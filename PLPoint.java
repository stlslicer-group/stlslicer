package stlslicer;

/**
 *A linked list element for the PolyLine class
 * @author Josh
 */
public class PLPoint{

    
    Vector point;
    PLPoint next;
    
    public PLPoint(Vector newPoint){
        //clone can't handle a null vector so just set point to null in that case
        if(newPoint==null)
            point=null;
        else
            point=Vector.clone(newPoint);
        
        next=null;
    }
    
    public PLPoint getNext(){
        return next;
    }
    
    
}
