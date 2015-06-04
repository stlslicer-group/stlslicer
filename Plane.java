package stlslicer;

public class Plane {
    Vector normal;
    Vector x0;
    public Plane(Vector normal, Vector x0){
        this.normal = normal;
        this.x0 = x0;
    }
    
    public static boolean vectorInPlane(Plane p, Vector v){
        //returns true is vector v is in plane p using the dot product
        
        //If vector v is in the plane, it will be perpendicular to the normal of the plane
        //so the dot product will be zero
        double dot=Vector.dot(p.normal,v);
        
        if(dot==0){
            return true;
        }
        else{
            return false;
        }
    }
    
    public boolean vectorInPlane(Vector v){
        //returns true if vector v is in this plane
        
    //If vector v is in the plane, it will be perpendicular to the normal of the plane
        //so the dot product will be zero
        double dot=Vector.dot(this.normal,v);
        
        if(dot==0){
            return true;
        }
        else{
            return false;
        }
    }
    
    public boolean pointInPlane(Vector p){
        //returns true if p is a point in the plane
        //Determines this by using x0 and p and determing if it sastifies the equation of the plane
        
        //if v1,v2 and v3 are the components of the normal vector the equation of the plane is
        //v1*(x-x0)+v2*(y-y0)+v3*(z-z0)=0
        double planeEquation=this.normal.x*(p.x-this.x0.x)+this.normal.y*(p.y-this.x0.y)+this.normal.z*(p.z-this.x0.z);
        
        //if p sastifies the equation of the plane, planeEquation will be zero
        if(planeEquation==0){
            return true;
        }
        else{
            return false;
        }
    }
}
