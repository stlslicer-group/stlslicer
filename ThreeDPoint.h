#ifndef FILE_ThreeDPoint_SEEN
#define FILE_ThreeDPoint_SEEN

class ThreeDPoint {
	private:
		//private members
		float mX{0.0};
		float mY{0.0};
		float mZ{0.0};
	
	public:
		//constructor
		ThreeDPoint(float x, float y, float z);
		
		float getX() const;
		float getY() const;
		float getZ() const;
};

#endif

