#ifndef FILE_WriterParams_SEEN
#define FILE_WriterParams_SEEN

class WriterParams {
	private:
		//private members
		int mXViewWidth;
		int mYViewWidth;
		float mXTrans;
		float mYTrans;

	public: 

		WriterParams(int xViewWidth, int yViewWidth, float xTrans, float yTrans);

		int getXViewWidth() const;
		int getYViewWidth() const;
		float getXTrans() const;
		float getYTrans() const;
};

#endif

