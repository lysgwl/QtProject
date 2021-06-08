#ifndef ELS_BASE_ADAPTER_H
#define ELS_BASE_ADAPTER_H

class CElsBaseAdapter
{
public:
	CElsBaseAdapter();
	virtual ~CElsBaseAdapter();

public:
	//½âÎöjsonÊý¾Ý¶Î
	bool elsParseSegment(const QJsonObject &json, int iPkgType, void *pstPkgEvent);	
	
protected:
	bool parseSegment(int iPkgType, void *pstPkgEvent, std::vector<std::tuple<std::string, std::string>> &vecTuple);	
};

#endif