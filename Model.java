package stlslicer;

public class Model {
    int numFacets;
	//use something smarter than built in array type?
    Facet[] f;
    public Model(int number_of_facets){
        numFacets = number_of_facets;
		//allocate array in constructor
        f = new Facet[numFacets];
    }
	
	//n should be internally maintained by the facet class?
    public void defineFacet(int n, Vector A, Vector B, Vector C){
        f[n] = new Facet(A,B,C);
        //System.out.println("Defined Facet " + n);
    }
    //returns an array of two vectors defining the extents of the model
    //the 1st vector gives the minimum in each dimension, 
    //the 2nd vector gives the maximum in each dimension

	//can keep track of min and max point while creating the facets or whatnot
    public Extents getExtents(){
        //TODO Clean this up eventually (made this before Extents class)
        Vector[] v = new Vector[2];
        v[0] = new Vector(0,0,0);
        v[1] = new Vector(0,0,0);
        for(int i = 0; i < numFacets; i++){
            //get min in x
            if(f[i].A.x < v[0].x) v[0].x = f[i].A.x;
            if(f[i].B.x < v[0].x) v[0].x = f[i].B.x;
            if(f[i].C.x < v[0].x) v[0].x = f[i].C.x;
            //get min in y
            if(f[i].A.y < v[0].y) v[0].y = f[i].A.y;
            if(f[i].B.y < v[0].y) v[0].y = f[i].B.y;
            if(f[i].C.y < v[0].y) v[0].y = f[i].C.y;
            //get min in z
            if(f[i].A.z < v[0].z) v[0].z = f[i].A.z;
            if(f[i].B.z < v[0].z) v[0].z = f[i].B.z;
            if(f[i].C.z < v[0].z) v[0].z = f[i].C.z;
            //get max in x
            if(f[i].A.x > v[1].x) v[1].x = f[i].A.x;
            if(f[i].B.x > v[1].x) v[1].x = f[i].B.x;
            if(f[i].C.x > v[1].x) v[1].x = f[i].C.x;
            //get max in y
            if(f[i].A.y > v[1].y) v[1].y = f[i].A.y;
            if(f[i].B.y > v[1].y) v[1].y = f[i].B.y;
            if(f[i].C.y > v[1].y) v[1].y = f[i].C.y;
            //get max in z
            if(f[i].A.z > v[1].z) v[1].z = f[i].A.z;
            if(f[i].B.z > v[1].z) v[1].z = f[i].B.z;
            if(f[i].C.z > v[1].z) v[1].z = f[i].C.z;
        }
        Extents ex = new Extents();
        ex.min = v[0];
        ex.max = v[1];
        return(ex);
    }
    public void scale(double s){
        //multiply each coord in model by s
        for(int i=0; i < numFacets; i++){
            f[i].A.x = f[i].A.x*s;
            f[i].A.y = f[i].A.y*s;
            f[i].A.z = f[i].A.z*s;
            f[i].B.x = f[i].B.x*s;
            f[i].B.y = f[i].B.y*s;
            f[i].B.z = f[i].B.z*s;
            f[i].C.x = f[i].C.x*s;
            f[i].C.y = f[i].C.y*s;
            f[i].C.z = f[i].C.z*s;
        }
    }
    public void scale(Extents e){
        //multiply and translate coords to match new extents e
        //FIRST: multiply
        //scale factor in each dimension
        double xs, ys, zs;
        Extents currentE = this.getExtents();
        xs = (e.max.x-e.min.x)/(currentE.max.x-currentE.min.x);
        ys = (e.max.y-e.min.y)/(currentE.max.y-currentE.min.y);
        zs = (e.max.z-e.min.z)/(currentE.max.z-currentE.min.z);
        for(int i=0; i < numFacets; i++){
            f[i].A.x = f[i].A.x*xs;
            f[i].A.y = f[i].A.y*xs;
            f[i].A.z = f[i].A.z*xs;
            f[i].B.x = f[i].B.x*ys;
            f[i].B.y = f[i].B.y*ys;
            f[i].B.z = f[i].B.z*ys;
            f[i].C.x = f[i].C.x*zs;
            f[i].C.y = f[i].C.y*zs;
            f[i].C.z = f[i].C.z*zs;
        }
        //translation in each dimension
        currentE = this.getExtents();
        double xt,yt,zt;
        
        xt = currentE.max.x-e.max.x;
        yt = currentE.max.y-e.max.y;
        zt = currentE.max.z-e.max.z;
        
        Vector t = new Vector(xt,yt,zt);
        for(int i=0; i < numFacets; i++){
            f[i].A = Vector.sub(f[i].A,t);
            f[i].B = Vector.sub(f[i].B,t);
            f[i].C = Vector.sub(f[i].C,t);
        }
    }
}

