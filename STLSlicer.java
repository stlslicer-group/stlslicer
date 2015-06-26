package stlslicer;

import java.io.*;

public class STLSlicer {

    STLSlicer s = new STLSlicer();
    
    
    public static void main(String[] args) throws FileNotFoundException, 
            IOException{
        final int numSlices = 200;
        
        System.out.println("loadModel");
        Model m = loadModel("/home/daniel/Desktop/porsche.stl");
       
		//arbitrary scale by 10
        m.scale(10.0);
        Extents e = m.getExtents();
		//the min and max 3D coords
        printVect(e.max);
        printVect(e.min);
        
		//allocate slices
        Slice[] s = new Slice[numSlices];

		//create the set number of slices 
        for (int i = 0; i < numSlices; i++){
			//create a new plane in with a normal of 1,  and the definition of the current plane
			//Dont compute the slice width every time; make const
            Plane p = new Plane(new Vector(1,0,0),
                    new Vector((double)(((e.max.x-e.min.x)/numSlices)*i+(double)e.min.x),0,0));
            
            LineSegment[] lines = Slicer(m,p);
            /*
            LineSegment[] newLines = LineSegment.changeBasis(p, lines);
            
            //if either the x or y components are negative, make them positive
            for(int j=0;j<newLines.length;j++){
                if(newLines[j].v1.x<0)
                    newLines[j].v1.x=newLines[j].v1.x*-1;
                if(newLines[j].v1.y<0)
                    newLines[j].v1.y=newLines[j].v1.y*-1;                
                if(newLines[j].v2.x<0)
                    newLines[j].v2.x=newLines[j].v2.x*-1;
                if(newLines[j].v2.y<0)
                    newLines[j].v2.y=newLines[j].v2.y*-1;                             
            }
            
            //creates a new slice - should be in order
            //s[i] = new Slice(newLines);
            */
            //TODO: make Slice.parametrize(Slice[],Double)
            //Slice.parametrize(s,resolution);
            
            writeToSVG(lines, "/home/daniel/Desktop/SlicerSVG/"
                    + "STLSlicerOutput"+i+".svg",(int)e.max.x,(int)e.max.y);
        }
    }
    
    //Writes an array of LineSegments to an SVG file
    public static void writeToSVG(LineSegment[] l, String fileName,int x, int y) 
            throws IOException{
        BufferedWriter out = new BufferedWriter(
                new FileWriter(fileName));
        // all the svg shit that comes before the path
        out.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\""
                + "?>\n<svg\nversion=\"1.1\"\nwidth=\""+x+"\"\nheight=\""+y+"\""
                + "\nid=\"svg2\">\n<defs\nid=\"defs4\" />\n");
        
        String coords;
        //write the path
            //form a string that looks like "M x,y x,y x,y x,y z"
        for(int i = 0; i < l.length; i++){
            out.write("<path\nstyle=\""
                    + "fill:none;stroke:#000000;stroke-width:3px;stroke-linecap:"
                    + "butt;stroke-linejoin:miter;stroke-opacity:1\"");
            coords = "d=\"M ";
            //System.out.println("l.length = "+l.length);

            coords+=String.valueOf(l[i].v1.x);
            coords+=",";
            coords+=String.valueOf(l[i].v1.y);
            coords+=" ";
            coords+=String.valueOf(l[i].v2.x);
            coords+=",";
            coords+=String.valueOf(l[i].v2.y);
            coords+="\"\nid=\"path"+String.valueOf(i)+"\"\n/>";
            out.write("\n"+coords+"\n");
        }
        
        //the shit that comes after the path
        out.write("</svg>");
        out.close();
    }

    // returns an array of line segments representing where a plane crosses 
    // a model
    public static LineSegment[] Slicer(Model m, Plane p){
        int n = 0; //number of intersecting facets
        //find n and declare appropriately sized array of lines
		//is this where OpenCL will come in?
        for(int i = 0; i < m.numFacets; i++){
            if(intersects(m.f[i], p)){
                n++;
            }
        }
        //System.out.println(n);

		//make as many LineSegments as intersections which were found
        LineSegment[] s = new LineSegment[n];
        
        //fill array with the lines of intersection
        int count=0;
        for(int i = 0; i < m.numFacets; i++){
            if(intersects(m.f[i], p)){
                //printVect(intersection(m.f[i],p).v1);
                //printVect(intersection(m.f[i],p).v2);
                s[count++] = intersection(m.f[i],p);
            }
        }
        return(s);
    }
    //returns boolean indicating whether a facet intersects a plane
    public static boolean intersects(Facet f, Plane p){
        double[] t = new double[3];
        boolean b = false;
        short n = 0;
        //calculate t of intersection for each line segment
        t[0] = Vector.dot(p.normal,Vector.sub(p.x0, f.A))/Vector.dot(p.normal,Vector.sub(f.B,f.A));
        t[1] = Vector.dot(p.normal,Vector.sub(p.x0, f.A))/Vector.dot(p.normal,Vector.sub(f.C,f.A));
        t[2] = Vector.dot(p.normal,Vector.sub(p.x0, f.B))/Vector.dot(p.normal,Vector.sub(f.C,f.B));
        
        //if t is between 0 and 1 for exactly 2 line segments, it intersects 
        // ie return(true)
        for(int i = 0; i < 3; i++){
            if(t[i] >= 0 && t[i] <= 1){
                n++;
            }
        }
        if (n==2){
            b = true;
        } else {
            b = false;
        }
        return(b);
    }
    //returns the LineSegment where a facet intersects a face
    public static LineSegment intersection(Facet f, Plane p){
        Vector v1, v2;
        double[] t = new double[3];
        
        //calculate the t where the line is 
        t[0] = Vector.dot(p.normal,Vector.sub(p.x0, f.A))/Vector.dot(p.normal,Vector.sub(f.B,f.A));
        t[1] = Vector.dot(p.normal,Vector.sub(p.x0, f.A))/Vector.dot(p.normal,Vector.sub(f.C,f.A));
        t[2] = Vector.dot(p.normal,Vector.sub(p.x0, f.B))/Vector.dot(p.normal,Vector.sub(f.C,f.B));
        
        //use whichever t[]'s that are between 0 and 1
        //plug them into the line equation to obtain v1 & v2
        if(!(t[0]>=0 && t[0]<=1) | Double.isNaN(t[0]) | Double.isInfinite(t[0])){
            //v1 and v2 use t[1] and t[2]
            //v1 is on the line from A to C
            v1 = Vector.add(Vector.scalarMultiple((1-t[1]), f.A),Vector.scalarMultiple(t[1],f.C));
            //v2 is on the line from B to C
            v2 = Vector.add(Vector.scalarMultiple((1-t[2]), f.B),Vector.scalarMultiple(t[2],f.C));
        } else if(!(t[1]>=0 && t[1]<=1) | Double.isNaN(t[1]) | Double.isInfinite(t[1])){
            //v1 and v2 use t[0] and t[2]
            //v1 is on the line from A to B
            v1 = Vector.add(Vector.scalarMultiple((1-t[0]), f.A),Vector.scalarMultiple(t[0],f.B));
            //v2 is on the line from B to C
            v2 = Vector.add(Vector.scalarMultiple((1-t[2]), f.B),Vector.scalarMultiple(t[2],f.C));
        } else if(!(t[2]>=0 && t[2]<=1) | Double.isNaN(t[2]) | Double.isInfinite(t[2])){
            //v1 and v2 use t[0] and t[1]
            //v1 is on the line from A to B
            v1 = Vector.add(Vector.scalarMultiple((1-t[0]), f.A),Vector.scalarMultiple(t[0],f.B));
            //v2 is on the line from A to C
            v2 = Vector.add(Vector.scalarMultiple((1-t[1]), f.A),Vector.scalarMultiple(t[1],f.C));
        } else {
            System.out.println("NULL IN INTERSECTION CLASS!");
            v1 = null;
            v2 = null;
        }
        return(new LineSegment(v1,v2));
    }
    
    //A shortcut to printing vectors for debug purposes
    public static void printVect(Vector v){
        System.out.println("<"+v.x+","+v.y+","+v.z+">");
    }

    // loads an ascii stl file (WITH EXTREMELY SPECIFIC FORMATTING PRODUCED BY
    // MESHLAB) into a Model object
    public static Model loadModel(String fileName)
            throws FileNotFoundException, IOException{
        String line, A, B, C;
        //count the number of facets in the file
        BufferedReader count = new BufferedReader(
                new FileReader(fileName));
        int numberOfFacets = 0;
        while ((line = count.readLine()) != null){
            if(line.contains("outer loop") == true){
				numberOfFacets++;
			} 
        }
        count.close();
        Model m = new Model(numberOfFacets);
        System.out.println("Number of facets in model: " + numberOfFacets);
        //save vertices of each face to the model
        int i = 0;
        BufferedReader in = new BufferedReader(
                new FileReader(fileName));
        while ((line = in.readLine()) != null){
            if(line.contains("outer loop") == true){
				//each of A B and C represent a 3D point
                A = in.readLine().substring(14, 55);
                B = in.readLine().substring(14, 55);
                C = in.readLine().substring(14, 55);
                m.defineFacet(i, new Vector(A),new Vector(B),new Vector(C));
                i++;
            }
        }
        in.close();
        return(m);
    }
}
