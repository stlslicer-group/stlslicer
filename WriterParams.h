#ifndef FILE_WriterParams_SEEN
#define FILE_WriterParams_SEEN

class WriterParams {
	private:
		//private members
		int mZViewHeight;
		int mYViewWidth;
		float mYTrans;
		float mZTrans;

	public: 

		WriterParams(int zViewHeight, int yViewWidth, float yTrans, float zTrans);

		int getZViewHeight() const;
		int getYViewWidth() const;
		float getYTrans() const;
		float getZTrans() const;
};

#endif

