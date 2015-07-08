#ifndef FILE_Error_SEEN
#define FILE_Error_SEEN

#include <string>

class FileFailedToOpenError {

	private:
		std::string mErrorMessage;

	public:
		FileFailedToOpenError(std::string errorMessage) : mErrorMessage{errorMessage} {}
		std::string getErrorMessage() const{
			return mErrorMessage;
		}		
			
};

class FileFailedToBeCreatedError {

	private:
		std::string mErrorMessage;

	public:
		FileFailedToBeCreatedError(std::string errorMessage) : mErrorMessage{errorMessage} {}
		std::string getErrorMessage() const{
			return mErrorMessage;
		}		
			
};

#endif

