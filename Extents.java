package stlslicer;

public class Extents {
    Vector min;
    Vector max;
    public Extents(Vector min,Vector max){
        this.min = min;
        this.max = max;
    }
    public Extents(){
        min = null;
        max = null;
    }
}
