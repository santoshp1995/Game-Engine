//#include "ClipList.h"
//
//namespace Azul
//{
//	ClipList::ClipList()
//	{
//		this->pActiveClip = nullptr;
//		this->pHeadClip = nullptr;
//	}
//
//	ClipList::~ClipList()
//	{
//		this->Clear();
//	}
//
//	void ClipList::Add(Clip* _pClip)
//	{
//		this->privAddToFront(_pClip);
//	}
//
//	void ClipList::MoveToNextClip()
//	{
//		if (this->pActiveClip->GetNext() != nullptr)
//			this->pActiveClip = pActiveClip->GetNext();
//
//		else
//			this->pActiveClip = this->pHeadClip;
//
//	}
//
//	Clip* ClipList::GetActiveClip() const
//	{
//		return this->pActiveClip;
//	}
//
//	void ClipList::privAddToFront(Clip* pClip)
//	{
//		// head is null
//		if (this->pHeadClip == nullptr)
//		{
//			this->pHeadClip = pClip;
//			this->pHeadClip->SetNext(nullptr);
//			this->pHeadClip->SetPrev(nullptr);
//		}
//
//		else
//		{
//			Clip* pTmp = pClip;
//
//			pTmp->SetNext(this->pHeadClip);
//			pTmp->SetPrev(nullptr);
//			this->pHeadClip->SetPrev(pTmp);
//
//			this->pHeadClip = pTmp;
//		}
//
//		this->pActiveClip = this->pHeadClip;
//	}
//
//	void ClipList::Clear()
//	{
//		Clip* pTmp = this->pHeadClip;
//
//		while (pTmp != nullptr)
//		{
//			Clip* pDeleteMe = pTmp;
//			pTmp = pTmp->GetNext();
//			delete pDeleteMe;
//		}
//	}
//}
