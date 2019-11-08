#ifndef __IMAGEPROCESS_H__
#define __IMAGEPROCESS_H__

class ImageProcess
{
public:
	ImageProcess();
	~ImageProcess();
	
public:
	bool	loadImage(const QString &filename);
	
	void 	deskew();
};

#endif