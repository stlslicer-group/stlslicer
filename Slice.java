package stlslicer;

import java.util.LinkedList;
/**
 *
 * @author daniel
 */
public class Slice {
    
    // The list of PolyLines (i.e. a linked list of linked lists)
    // pll stands for PolyLine List
    LinkedList<PolyLine> pll = new LinkedList<>();
    public Slice(LineSegment[] lines){
        // the maximum distance apart vectors can be to be considered the same
        double overlapDist = 0.000001;
        // indicates whether lineSegments were joined or if a new poly line
        // needs to be created
        boolean foundSomething = false;
        // keeps track of which index of the array the new PolyLine starts on
        int plStart = 0;
        // ISSUE: need more information than just vertices
        //  Need line segments to preserve information about the shape
        //  Entire line segments will be sorted
        //  Must use array for sorting
        LineSegment buff;
        for(int i = 0; i < lines.length-1; i++){
        //sort section
            //compare lines[i] to every line after itself
            for(int j = i+1; j < lines.length; j++){
                // if another line whose v1 is equal to this line's v2, it 
                // should come after this one. Swap the other line with the 
                // next line in this array
                if(Vector.isWithin(lines[j].v1,lines[i].v2,overlapDist)){
                    //swap lines[i+1] and lines[j]
                    buff = lines[i+1];
                    lines[i+1] = lines[j];
                    lines[j] = buff;
                    foundSomething = true;
                }
            }
            // if no other line connects to this one's endpoint
            if(!foundSomething){
                //create a new PolyLine in the list of lists
                pll.add(new PolyLine());
                //convert lines[] to PolyLine
                // NOTE: This will not close the shape. The boolean in PolyLine 
                // should be used later to close the gap using the first vector
                for(int k = plStart; k <= i; k++){
                    pll.getLast().add(lines[k].v1);
                }
                plStart = i;
            }
        }
    }
}
