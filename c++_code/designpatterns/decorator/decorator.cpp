/*
 * 使用到组合优于对象继承的原则，动态的给子类添加功能
 * 继承会带来一些静态特性和多子类衍生的问题
 * decorator解决的目标并不是“多子类衍生的多继承”问题，
 * 而是应用在“主体类在多个方向上的扩展功能”
 * */

class Stream
{
public:
	virtual char Read(int pCount) = 0;

	virtual void Seek(int pPosition) = 0;

	virtual void Write(char data) = 0;

	virtual ~Stream();
};

class FileStream : public Stream
{
public:
	 char Read(int pCount)
	 {
		 //读文件流
	 }

	 void Seek(int pPosition)
	 {
		 //定位文件流
	 }

	 void Write(char data)
	 {
		 //写文件流
	 }

	 ~FileStream()
	 {
	 }
}

class NetworkStream : public Stream
{
public:
	 char Read(int pCount)
	 {
		 //读网络流
	 }

	 void Seek(int pPosition)
	 {
		 //定位网络流
	 }

	 void Write(char data)
	 {
		 //写网络流
	 }

	 ~NetworkStream()
	 {
	 }
}

class MemoryStream : public Stream
{
public:
	 char Read(int pCount)
	 {
		 //读内存流
	 }

	 void Seek(int pPosition)
	 {
		 //定位内存流
	 }

	 void Write(char data)
	 {
		 //写内存流
	 }

	 ~MemoryStream()
	 {
	 }
}

class DecoratorStream : public Stream
{
public:
	virtual ~DecoratorStream();

protected:
	DecoratorStream(Stream *pStream);

	Stream *mStream;
};

class CryptoStream : public DecoratorStream
{
public:
	CryptoStream(Stream *pStream) : DecoratorStream(pStream)
	{}

	 char Read(int pCount)
	 {
		 //加密操作
		 mStream->Read();
	 }

	 void Seek(int pPosition)
	 {
		 //加密操作
		 mStream->Seek();
	 }

	 void Write(char data)
	 {
		 //加密操作
		 mStream->Write();
	 }
};


class BufferStream : public DecoratorStream
{
public:
	BufferStream(Stream *pStream) : DecoratorStream(pStream)
	{}

	 char Read(int pCount)
	 {
		 //缓冲操作
		 mStream->Read();
	 }

	 void Seek(int pPosition)
	 {
		 //缓冲操作
		 mStream->Seek();
	 }

	 void Write(char data)
	 {
		 //加密操作
		 mStream->Write();
	 }
};

int main(int argc, char *argv[])
{
	//运行时装配
	FileStream *s1 = new FileStream();
	CryptoStream *s2 = new CryptoStream(s1); //给文件流加密操作
	BufferStream *s3 = new BufferStream(s1); //给文件流进行缓冲操作
	BufferStream *s4 = new BufferStream(s2); //给文件加密流进行缓冲操作
}
