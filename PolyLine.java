package stlslicer;

/**
 *
 * A series of vectors with the next vector in the list being the next point in the polyline
 * The linked list has a null header
 */
public class PolyLine {
    PLPoint head;
    PLPoint tail;
    Boolean connected;
    
    PolyLine(){
        head=new PLPoint(null);
        tail=new PLPoint(null);
        head.next=tail;
        connected=false;
    }
    
    public void setConnected(){
   //changes the connected variable to indicate that the polyline is connected
        this.connected=true;
    }
    
    public void clearConnected(){
    //changes the connected variable to indicate that the polyline is not longer connected
        
        this.connected=false;
    }
    
    public PLPoint add(Vector newVector){
    
        tail.next=new PLPoint(null);
        tail.point=Vector.clone(newVector);
        PLPoint newPoint=tail;
        tail=tail.next;
        
        return newPoint;
    }
    
    public static void printPolyLine(PolyLine pl){
        //prints all the vectors in the polyline
        
  
        PLPoint p=pl.head;
        while(p.next!=null){
            p.next.point.printVect();
            p=p.next;
        }
    }
    public void printPolyLine(){
    //non static version of printPolyLine
        PolyLine.printPolyLine(this);
    }
    
    public boolean isConnecter(){
    //returns the connected variable
        return this.connected;
    }
    
    public void removeNext(PLPoint previous){
    //removes the element after the passed in point
        //If previous is the last element in the list, do nothing
        
        if(previous.next==null){
            return;
        }
        
        previous.next=previous.next.next;
        
        //handle the case where the last element was removed
        if(previous.next==null){
            tail=previous;
        }
    }
}


