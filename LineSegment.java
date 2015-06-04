package stlslicer;

//Two vectors in one object
public class LineSegment{
    Vector v1;
    Vector v2;
    // Start point and end point
    public LineSegment(Vector v1, Vector v2){
        this.v1 = v1;
        this.v2 = v2;
    }
    public static LineSegment changeBasis(Plane basisPlane, LineSegment line){
        //changes the basis of this vector to a basis based on the input plane
        //The goal is to find 2 vectors that are perpendicular to eachother that are in the plane
        //The first one is the vector between a random point and x0. The second one
        //is the cross product of this first direction and the normal 


        //the vector and x0 of the basis plane
        Vector normal=Vector.clone(basisPlane.normal);
        Vector x0=basisPlane.x0;
        
        // copy of argument to avoid modifying it
        LineSegment l = clone(line);

        
        //Find a random point with x=0,y=0 and use x0 and the normal to find z
        Vector randomPoint=new Vector(0,0,(normal.x*x0.x+normal.y*x0.y+normal.z*x0.z)/normal.z);
        //if the random point is the same as x0, use a random point where x=1,y=1, using the normal and x0 to find z
        if(Vector.isEqual(randomPoint, x0)){
            randomPoint=new Vector(1,1,(normal.x*(x0.x-1)+normal.y*(x0.y-1)+normal.z*x0.z)/normal.z);
        }

        
        //the first basis direction is the vector from x0 to the random point
        Vector d1=new Vector(x0,randomPoint);
        
        
        //the other basis direction is the normal crossed with d1
        Vector d2=Vector.cross(d1,normal);



        //the new components of the line's vectors will now be the x and y components dotted with the new basises
        //need to put the x component in a temporary variable until the dot product with y is done
        double temp=Vector.dot(l.v1, d1);
        l.v1.y=Vector.dot(l.v1, d2);
        l.v1.x=temp;
        //set z to 0 since that is the point of change basis
        l.v1.z=0;

        temp=Vector.dot(l.v2, d1);
        l.v2.y=Vector.dot(l.v2, d2);
        l.v2.x=temp;
        l.v2.z=0;

        return(l);
    }
    
    public static LineSegment changeBasis(Plane basisPlane, LineSegment line,Vector orientation){
        //changes the basis of this vector to a basis based on the input plane
        //The orientation parametere tells the method which way is up so
        //The up direction (the y component) is in the direction of the orientation vection
        //and the right direction (the x component) is in the direction that is the orientation crossed witht the normal


        //the vector and x0 of the basis plane
        Vector normal=Vector.clone(basisPlane.normal);
        Vector x0=basisPlane.x0;
        
        // copy of argument to avoid modifying it
        LineSegment l = clone(line);

        
        
        //the first basis direction is the right direction so cross the orientation 
        //with the normal
        Vector d1=Vector.cross(orientation, normal);
        d1=Vector.div(d1, d1.mag());
        
        
        //the other basis direction is the up direction which is the orientation vector
        Vector d2=orientation;
        d2=Vector.div(d2, d2.mag());


        //the new components of the line's vectors will now be the x and y components dotted with the new basises
        //need to put the x component in a temporary variable until the dot product with y is done
        double temp=Vector.dot(l.v1, d1);
        l.v1.y=Vector.dot(l.v1, d2);
        l.v1.x=temp;
        //set z to 0 since that is the point of change basis
        l.v1.z=0;

        temp=Vector.dot(l.v2, d1);
        l.v2.y=Vector.dot(l.v2, d2);
        l.v2.x=temp;
        l.v2.z=0;

        return(l);
    }
    
    public void rotateLine(Vector upDirection, Vector rightDirection){
    //rotates this linesegment so that it's y component corresponds to the upDirection
        //and its x component corresponds to the rightDirection
        
        Vector yBasis=Vector.clone(upDirection);
        Vector xBasis=Vector.clone(rightDirection);
        //find the third basis by taking the cross product
        Vector zBasis=Vector.cross(xBasis,yBasis);
        
        //normalize the new basis vectors
        yBasis=Vector.div(yBasis,yBasis.mag());
        xBasis=Vector.div(xBasis,xBasis.mag());
        zBasis=Vector.div(zBasis,zBasis.mag());
        
        Vector temp1=Vector.clone(this.v1);
        Vector temp2=Vector.clone(this.v2);
        //the new x and ycomponent will be the current vectors dotted with the x and y basis vectors
        //the new z will be the z component dotted with the normal vector
        this.v1.x=Vector.dot(temp1, xBasis);
        this.v2.x=Vector.dot(temp2, xBasis);
        this.v1.y=Vector.dot(temp1, yBasis);
        this.v2.y=Vector.dot(temp2, yBasis);
        this.v1.z=Vector.dot(temp1, zBasis);
        this.v2.z=Vector.dot(temp2, zBasis);
    }
    
    //NOTE: this is not optimized for memory - it makes a copy of lines
    public static LineSegment[] changeBasis(Plane basisPlane,LineSegment[] lines){
    //takes an array of line segments and changes the basis to the desired plane,
        //see changeBasis(Plane p) for more details regarding changing basis
        LineSegment[] newLines = new LineSegment[lines.length];
        //TEMP DEBUG finding average z value
        double avgZ = 0;
        for(int i=0;i<lines.length;i++){
            newLines[i] = changeBasis(basisPlane,lines[i]);
            avgZ += newLines[i].v1.z;
            avgZ += newLines[i].v2.z;
            if(Double.isNaN(avgZ)){
                System.out.println("NaN, foo");
            }
        }
        avgZ /= 2*newLines.length;
       // System.out.println("in LineSegment.changeBasis(), average z component: "
         //       + avgZ);
        return(newLines);
    }
    
    public static LineSegment clone(LineSegment l){
        //creates a copy of the input line
        
        //clone the LineSegment's two vectors
        Vector v1=l.v1;
        Vector v2=l.v2;
        
        //create a new LineSegment and return it
        return new LineSegment(v1,v2);
    }
    
}


