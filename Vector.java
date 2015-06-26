package stlslicer;

//class name should be changed to Point
public class Vector {
    double x;
    double y;
    double z;
    byte dim;
    public Vector(double x, double y, double z){
        this.x = x;
        this.y = y;
        this.z = z;
        dim = 3;
    }
    /*
    public Vector(double x, double y){
        this.x = x;
        this.y = y;
        dim = 2;
    }
    */
    
	//constructor accepting string and parsing three coords
    public Vector(String stlString){
        String[] component = Vector.splitString(stlString);
        this.x = Double.parseDouble(component[0].substring(0,component[0].indexOf("e")))
                *Math.pow(10,Integer.parseInt(component[0].substring(component[0].indexOf("e")+1,component[0].length())));
        this.y = Double.parseDouble(component[1].substring(0,component[1].indexOf("e")))
                *Math.pow(10,Integer.parseInt(component[1].substring(component[1].indexOf("e")+1,component[1].length())));
        this.z = Double.parseDouble(component[2].substring(0,component[2].indexOf("e")))
                *Math.pow(10,Integer.parseInt(component[2].substring(component[2].indexOf("e")+1,component[2].length())));
        //System.out.println("Added Vector: <"+this.x+","+this.y+","+this.z+">"+"\n");
    }
    
    public Vector(Vector start, Vector end){
        //creates a vector that points from start to end
        
        this.x=end.x-start.x;
        this.y=end.y-start.y;
        this.z=end.z-start.z;
    }
    
    public static Vector sub(Vector a,Vector b){
        //if(a.dim==3&&b.dim==3){
            return(new Vector(a.x-b.x,a.y-b.y,a.z-b.z));
        //}else{
        //    return(new Vector(a.x-b.x,a.y-b.y));
        //}
    }
    public static Vector add(Vector a, Vector b){
        //if (a.dim==3&&b.dim==3){
            return(new Vector(a.x+b.x,a.y+b.y,a.z+b.z));
        //}else{
        //    return(new Vector(a.x+b.x,a.y+b.y));
        //}
    }
    public static double dot(Vector a,Vector b){
        //if(a.dim==3&&b.dim==3){
            return(a.x*b.x+a.y*b.y+a.z*b.z);
        //} else {
        //    return(a.x*b.x+a.y*b.y);
        //}
    }
    public static Vector cross(Vector a,Vector b){
        //if(a.dim==3&&b.dim==3){
            return(new Vector(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x));
        //}else{
        //   return(new Vector(0,0,(a.x*b.y-a.y*b.x)));
        //}
    }
    public double mag(){
        return(Math.sqrt(Math.pow(this.x,2)+Math.pow(this.y,2)
                +Math.pow(this.z,2)));
    }
    public static double mag(Vector v){
        return(Math.sqrt(Math.pow(v.x,2)+Math.pow(v.y,2)+Math.pow(v.z,2)));
    }
    public static Vector scalarMultiple(double d, Vector a){
        return(new Vector(a.x*d,a.y*d,a.z*d));
    }
    
    public static Vector clone(Vector v){
    //returns a new vector that is a copy of the input vector
        if(v==null)
            return null;
        else{
            Vector copy=new Vector(v.x,v.y,v.z);
            return copy;
        }
    }
    
    public void div(Double a){
    //divides this vector by a scalar        
        this.x=(double)this.x/a;
        this.y=(double)this.y/a;
        this.z=(double)this.z/a;
    }
    
    public static Vector div(Vector v, Double a){
    //divides the vector v by a scalar and returns it
        Vector newVector=Vector.clone(v);
        newVector.x=(double)newVector.x/a;
        newVector.y=(double)newVector.y/a;
        newVector.z=(double)newVector.z/a;
        
        return  newVector;   
    }
    
    
    public static String[] splitString(String str){
    //takes a string with elements separated with one or more commas and returns an 
        //array of strings
    //ie input: "apple bannana   ornage" return apple,bannana,ornage
        
        //temp will be modified throughout the method, this way the input is not changed
        String temp = new String(str);
        String[] elements = new String[3];
        int elementNumber = 0;
        
        //the first element may be a space so if so remove it
        if(temp.startsWith(" "))
            temp=temp.substring(1,temp.length());
        
        //split the array into 3 taking out only one space
        for(int i = 0; i < 3; i++){
            if(temp.indexOf(" ")!=-1){
                elements[elementNumber++]=temp.substring(0,temp.indexOf(" "));
                temp=temp.substring(temp.indexOf(" "),temp.length());                            
                                
                //removes the first leading zero
                if(temp.charAt(0)==' ')
                    temp=temp.substring(1,temp.length());
                //remove the second leading zero if it exists
                if(temp.charAt(0)==' ')
                    temp=temp.substring(1,temp.length());
            }
            //case where the last element is left
            else
                elements[elementNumber++]=temp.substring(0,temp.length());            
        }
        return elements;
    }
    
    public static void printVect(Vector v){
        //prints all the components of the vector
        if(v.dim==3){
            System.out.println("<"+v.x+","+v.y+","+v.z+">");
        }
        else{
            System.out.print("<"+v.x+","+v.y+">");
        }
    }
   
    public static boolean isEqual(Vector v1,Vector v2){
        //determines if the vectors v1 and v2 are the same
        //Returns true if they are the same, false otherwise
        if(v1.x==v2.x){
            if(v1.y==v2.y){
                if(v1.z==v2.z){
                    return true;
                }
            }
        }
        return false;
    }
    
    public boolean vectorInPlane(Plane p){
        //returns true if this vector is in plane p
        return p.vectorInPlane(this);
    }
    
    public boolean pointInPlane(Plane p){
        //returns true if this vector (which is a poitn) is in plane p
        return p.pointInPlane(this);
    }
    
    public void printVect(){
    //non static print vector method
        Vector.printVect(this);
    }

    //returns true if the vectors are closer together than 'dist'
    public static boolean isWithin(Vector v1, Vector v2, Double dist){
        //the distance is the magnitude of the difference of the vectors
        if(mag(sub(v1,v2))<=dist){
            return(true);
        }else{
            return(false);
        }
    }
    
    
}
