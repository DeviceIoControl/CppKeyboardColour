#pragma once

class IModelIdRetriever 
{
public:
	virtual uint32_t GetModelID() = 0;
	virtual ~IModelIdRetriever() = default;
};