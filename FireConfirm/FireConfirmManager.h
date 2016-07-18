#ifndef __LYNX_GAME_SERVER_GAME_MANAGER_FIRE_CONFIRM_MANAGER_H__
#define __LYNX_GAME_SERVER_GAME_MANAGER_FIRE_CONFIRM_MANAGER_H__

#include "../NetworkLib/MsgHdr.h"
#include "../PersistThreadMsg.h"
#include "../CommonLib/MsgfireInfoToJson.h"
#include "../CommonLib/FirePacket.h"
#include "../CommonLib/StagePacket.h"


#define OUT_OF_RANGE 1.2 //�����ֵ���ϵ��

namespace Lynx
{

	class Player;
	class PlayerFireConfirmData;


	struct CGConfirmDataReq
	{
		CGConfirmDataReq(): confirmID(0){}

		UInt32 confirmID;
 		List<Int32> confirmDataList;
		std::string strConfirmData;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{
				confirmID = root["confirmID"].asUInt();
				int itmp = 0;
				for(int i =0; i <root["confirmDataList"].size();i++)
				{
					itmp  = root["confirmDataList"].operator [](i).asInt();
					confirmDataList.insertTail(itmp);
				}
			}
		}
		 	
		LYNX_MESSAGE_1(FIRE_CONFIRM_DATA_REQ, CGConfirmDataReq,std::string, strConfirmData);
	};
	
	struct CGChapterStart
	{
		CGChapterStart(): stageID(0){}

		UInt32 stageID;
		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{
				stageID = root["chapterID"].asUInt();				
			}
		}

		LYNX_MESSAGE_1(CHAPTER_START_REQ, CGChapterStart,std::string, jsonStr);
	};
	struct ChapterStartResp	
	{
		ChapterStartResp(): chapterID(0),result(0){}

		UInt32 chapterID;
		UInt32 result;

		std::string convertDataToJson()
		{
			Json::Value root;     	
			root["chapterID"] = Json::Value(chapterID);
			root["result"] = Json::Value(result);
			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}

	};
	struct CGChapterLeave
	{
		CGChapterLeave(): chapterID(0){}

		UInt32 chapterID;
		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{
				chapterID = root["chapterID"].asUInt();
			}			
		}
		LYNX_MESSAGE_1(CHAPTER_LEAVE_REQ, CGChapterLeave,std::string, jsonStr);
	};
	struct ChapterLeaveResp	
	{
		ChapterLeaveResp(): chapterID(0),result(0){}

		UInt32 chapterID;
		UInt32 result;
		std::string convertDataToJson()
		{
			Json::Value root;     	
			root["chapterID"] = Json::Value(chapterID);
			root["result"] = Json::Value(result);
			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}

	};
	struct AwardMonsterDamage
	{
		UInt32 ID;	//�ֵ�ID
		UInt32 damageType;//���˺�״̬
		UInt32 times;//����

	};
	struct CGChapterEnd
	{
		CGChapterEnd(): chapterID(0),result(0),star(0){}

		UInt32 chapterID;
		UInt32 result;
		UInt32 star;//��ͨ�ؿ�Ϊ���������˸���Ϊ���ʱ��
		List<AwardMonsterDamage> awardMonsterList;
		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{
				chapterID = root["chapterID"].asUInt();
				result = root["result"].asUInt();
				star = root["star"].asUInt();

				AwardMonsterDamage awardMonsterDamage;
				for(int i =0; i <root["confirmDataList"].size();i++)
				{
					awardMonsterDamage.ID  = root["awardMonsterList"][i]["ID"].asUInt();
					awardMonsterDamage.damageType  = root["awardMonsterList"][i]["damageType"].asUInt();
					awardMonsterDamage.times  = root["awardMonsterList"][i]["times"].asUInt();
					awardMonsterList.insertTail(awardMonsterDamage);
				}
			}
		}
		LYNX_MESSAGE_1(CHAPTER_END_REQ, CGChapterEnd,std::string, jsonStr);
	};
	
	struct ChapterEndResp	
	{
		ChapterEndResp(): chapterID(0),result(0),star(0),recordBreaking(0){}

		UInt32 chapterID;
		UInt32 result;
		UInt32 star;//��ͨ�ؿ�Ϊ���������˸���Ϊ���ʱ��
		UInt32 recordBreaking;//1 �Ƽ�¼ 0 δ��
		Json::Value allAttr;//������Ʒ����
		List<Award> firstAwards;
		List<Award> awards;
		List<Goods> cost;
		List<Card> cards;
		List<Goods> intruderAwardList;
		List<Goods> monsterDropList;
		List<Goods> fixedList;
		List<Goods> ends;
		

		std::string convertDataToJson()
		{
			Json::Value root;     	
			root["chapterID"] = Json::Value(chapterID);
			root["result"] = Json::Value(result);
			root["star"] = Json::Value(star);
			root["recordBreaking"] = Json::Value(recordBreaking);

			for(List<Award>::Iter * it = awards.begin(); it != NULL; it = awards.next(it))			
			{
				Json::Value son;
				for(List<Goods>::Iter * iter = it->mValue.award.begin(); iter != NULL; iter = it->mValue.award.next(iter))
				{
					Json::Value leaf;
					leaf.append(iter->mValue.resourcestype);
					leaf.append(iter->mValue.subtype);
					leaf.append(iter->mValue.num);

					son["award"].append(leaf);
				}
				root["awards"].append(son);
			}

			for(List<Award>::Iter * it = firstAwards.begin(); it != NULL; it = firstAwards.next(it))			
			{
				Json::Value son;
				for(List<Goods>::Iter * iter = it->mValue.award.begin(); iter != NULL; iter = it->mValue.award.next(iter))
				{
					Json::Value leaf;
					leaf.append(iter->mValue.resourcestype);
					leaf.append(iter->mValue.subtype);
					leaf.append(iter->mValue.num);

					son["award"].append(leaf);
				}
				root["firstAwards"].append(son);
			}

			for(List<Card>::Iter * it = cards.begin(); it != NULL; it = cards.next(it))			
			{
				Json::Value son;
				for(List<Goods>::Iter * iter = it->mValue.card.begin(); iter != NULL; iter = it->mValue.card.next(iter))
				{
					Json::Value leaf;
					leaf.append(iter->mValue.resourcestype);
					leaf.append(iter->mValue.subtype);
					leaf.append(iter->mValue.num);
					son["card"].append(leaf);
				}
				root["cards"].append(son);
			}		

			for(List<Goods>::Iter * iter = monsterDropList.begin(); iter != NULL; iter = monsterDropList.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["monsterDropList"].append(son);
			}
			for(List<Goods>::Iter * iter = intruderAwardList.begin(); iter != NULL; iter = intruderAwardList.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["intruderAwardList"].append(son);
			}

			for(List<Goods>::Iter * iter = cost.begin(); iter != NULL; iter = cost.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["cost"].append(son);
			}

			
			for(List<Goods>::Iter * iter = fixedList.begin(); iter != NULL; iter = fixedList.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["fixedList"].append(son);
			}

			for(List<Goods>::Iter * iter = ends.begin(); iter != NULL; iter = ends.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["ends"].append(son);
			}
			root["allAttr"] = Json::Value(allAttr);

			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};

	struct CGisRecievedReq
	{
		CGisRecievedReq(): recievePacketID(0){}

		UInt32 recievePacketID;
		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{
				recievePacketID = root["recievePacketID"].asUInt();
			}			
		}
		LYNX_MESSAGE_1(RECIEVED_PACKET_REQ, CGisRecievedReq,std::string, jsonStr);
	};

	struct ChapterCounterResp	
	{
		List<KeyValue> keyValue;
		std::string convertDataToJson()
		{
			Json::Value root;     
			for (List<KeyValue>::Iter *it = keyValue.begin();it!= NULL;it=keyValue.next(it))
			{
				Json::Value son;
				son["key"] = Json::Value(it->mValue.key);
				son["key"] = Json::Value(it->mValue.value);
				root["keyValue"].append(son);
			}		
			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};

	struct CGChapterAwardCard
	{
		CGChapterAwardCard(): chapterID(0),flag(0){}

		UInt32 chapterID;
		UInt32 flag;
		std::string jsonStr;

		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{
				chapterID = root["chapterID"].asUInt();
				flag = root["flag"].asUInt();
			}
		}
		LYNX_MESSAGE_1(CHAPTER_AWARD_CARD_REQ, CGChapterAwardCard,std::string, jsonStr);
	};
	struct ChapterAwardCardResp
	{
		ChapterAwardCardResp(): chapterID(0),result(0){}

		UInt32 flag;
		UInt32 chapterID;
		UInt32 result; 
		List<Goods> award;
		List<Goods> cost;
		List<Goods> ends;

		std::string convertDataToJson()
		{
			Json::Value root;     	
			root["chapterID"] = Json::Value(chapterID);
			root["flag"] = Json::Value(flag);
			root["result"] = Json::Value(result);
			for(List<Goods>::Iter * iter = award.begin(); iter != NULL; iter = award.next(iter))
			{
				Json::Value son;
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["award"].append(son);
			}

			for(List<Goods>::Iter * iter = cost.begin(); iter != NULL; iter = cost.next(iter))
			{
				Json::Value son;
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["cost"].append(son);
			}
			for(List<Goods>::Iter * iter = ends.begin(); iter != NULL; iter = ends.next(iter))
			{
				Json::Value son;
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["ends"].append(son);
			}

			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};

	struct CGRelive
	{
		CGRelive(): flag (0){}

		UInt32 flag ;
		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{
				flag  = root["flag"].asUInt();
			}			
		}
		LYNX_MESSAGE_1(CHAPTER_RELIVE_REQ, CGRelive,std::string, jsonStr);
	};
	struct ReliveResp	
	{
		ReliveResp(): flag (0),result(0),reliveTimes(0),yuanbaoCost(0),coinCost(0){}

		UInt32 flag ;
		UInt32 result;
		UInt32 reliveTimes;//�������
		UInt32 yuanbaoCost;//Ԫ������
		UInt32 coinCost;//�������
		
		std::string convertDataToJson()
		{
			Json::Value root;     	
			root["flag "] = Json::Value(flag );
			root["result"] = Json::Value(result);
			root["reliveTimes"] = Json::Value(reliveTimes);
			root["yuanbaoCost"] = Json::Value(yuanbaoCost);
			root["coinCost"] = Json::Value(coinCost);

			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};
	

	struct CGFoods
	{
		CGFoods(): reqType(0),num(0){}
		UInt32 reqType;//1��ȡ��Ϣ��2��⿣�3���� 4 �����ӻ�� 5 ʹ��ʳ��1 6 ʹ��ʳ��2 7ʹ��ʳ��3
		UInt32 num;//����
		
		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{				
				reqType = root["reqType"].asUInt();	
				num = root["num"].asUInt();	
			}			
		}
		LYNX_MESSAGE_1(CHAPTER_FOOD_REQ, CGFoods,std::string, jsonStr);
	};

	struct FoodsResp
	{
		FoodsResp(): flag(0),needTime(0),viableAmount(0),viableNum(0),restbuyNumber(0),vipFoodLeftNumber(0),gold(0){}
		UInt32 flag;
		UInt32 needTime;//�ȴ�ʱ��
		UInt32 viableAmount;//�ܴ���
		UInt32 viableNum ;//��ʹ�ô���	
		UInt32 gold ;//Ԫ����
		List<UInt32> foodList ;//ʳ������
		UInt32 restbuyNumber ;//vipʣ�๺�����
		UInt32 vipFoodLeftNumber;//vip����ʳ��ʣ�����
		std::string convertDataToJson()
		{
			Json::Value root;     
			root["flag"] = Json::Value(flag);
			root["needTime"] = Json::Value(needTime);
			root["viableAmount"] = Json::Value(viableAmount);
			root["viableNum"] = Json::Value(viableNum);
			root["gold"] = Json::Value(gold);
			for (List<UInt32>::Iter *iter = foodList.begin();iter != NULL; iter = foodList.next(iter))
			{
				root["foodList"].append(iter->mValue);
			}
			root["restbuyNumber"] = Json::Value(restbuyNumber);
			root["vipFoodLeftNumber"] = Json::Value(vipFoodLeftNumber);
			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};

	struct CGStrength
	{
		CGStrength(): reqType(0),num(0),needSend(true){}
		UInt32 reqType;//1��ȡ��Ϣ��3���� 
		UInt32 num;//����
		bool needSend;//true = send

		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{				
				reqType = root["reqType"].asUInt();	
				num = root["num"].asUInt();	
			}			
		}
		LYNX_MESSAGE_1(CHAPTER_STRENGTH_REQ, CGStrength,std::string, jsonStr);
	};
	struct StrengthResp
	{
		StrengthResp(): flag(0),reqType(0),needTime(0),viableAmount(0),restbuyNumber(0),vipStrengthLeftNumber(0),gold(0){}
		UInt32 flag;//��result������1�ǳɹ�
		UInt32 reqType;//1��ȡ��Ϣ��3���� 
		UInt32 needTime;//�ȴ�ʱ��
		UInt32 viableAmount;//�������ֵ
		UInt32 gold ;//ʣ��Ԫ����
		UInt32 strength;//����
		UInt32 restbuyNumber ;//vip�������
		UInt32 vipStrengthLeftNumber;//���Թ����ܴ�������¼��ʱ��һ�Σ�����ʱ��ͻ�Ҫ�Լ���

		std::string convertDataToJson()
		{
			Json::Value root;     
			root["flag"] = Json::Value(flag);
			root["reqType"] = Json::Value(reqType);
			root["needTime"] = Json::Value(needTime);
			root["viableAmount"] = Json::Value(viableAmount);
			root["gold"] = Json::Value(gold);
			root["strength"] = Json::Value(strength);
			
			root["restbuyNumber"] = Json::Value(restbuyNumber);
			root["vipStrengthLeftNumber"] = Json::Value(vipStrengthLeftNumber);
			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};
	struct CGStageMopUp
	{
		CGStageMopUp(): id(0),mopUpType(0){}
		UInt32 id;//�ؿ�ID
		UInt32 mopUpType;//����
		List<UInt32> useList;//ʳ��1��ʳ��2��ʳ��3����Ӣ

		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{		
				id = root["id"].asUInt();	
				mopUpType = root["mopUpType"].asUInt();	
				for(UInt32 i=0;i<root["useList"].size();i++)
				{
					useList.insertTail(root["useList"][i].asUInt());
				}
			}			
		}
		LYNX_MESSAGE_1(CHAPTER_MOP_UP_REQ,CGStageMopUp,std::string, jsonStr);
	};

	struct StageMopUpResp
	{
		StageMopUpResp(): id(0),mopUpType(0),result(0),leftTimes(0),mopupTimes(0){}
		UInt32 id;
		UInt32 mopUpType;
		UInt32 result;
		UInt32 leftTimes;//ʣ�����	
		UInt32 mopupTimes;
		Json::Value allAttr;//������Ʒ����
		List<UInt32> foodList ;//ʳ������

		List<Goods> fixedList;
		List<Award> awards;
		List<Goods> cost;
		List<Card> cards;
		List<Goods> monsterDropList;
		List<Award> firstAwards;
		List<Goods> ends;

		std::string convertDataToJson()
		{
			Json::Value root;     	
			root["id"] = Json::Value(id );
			root["mopUpType"] = Json::Value(mopUpType);
			root["result"] = Json::Value(result );		
			root["leftTimes"] = Json::Value(leftTimes);
			root["mopupTimes"] = Json::Value(mopupTimes);
			

			for(List<Award>::Iter * it = awards.begin(); it != NULL; it = awards.next(it))			
			{
				Json::Value son;
				for(List<Goods>::Iter * iter = it->mValue.award.begin(); iter != NULL; iter = it->mValue.award.next(iter))
				{
					Json::Value leaf;
					leaf.append(iter->mValue.resourcestype);
					leaf.append(iter->mValue.subtype);
					leaf.append(iter->mValue.num);

					son["award"].append(leaf);
				}
				root["awards"].append(son);
			}
			for(List<Award>::Iter * it = firstAwards.begin(); it != NULL; it = firstAwards.next(it))			
			{
				Json::Value son;
				for(List<Goods>::Iter * iter = it->mValue.award.begin(); iter != NULL; iter = it->mValue.award.next(iter))
				{
					Json::Value leaf;
					leaf.append(iter->mValue.resourcestype);
					leaf.append(iter->mValue.subtype);
					leaf.append(iter->mValue.num);

					son["award"].append(leaf);
				}
				root["firstAwards"].append(son);
			}

			for(List<Card>::Iter * it = cards.begin(); it != NULL; it = cards.next(it))			
			{
				Json::Value son;
				for(List<Goods>::Iter * iter = it->mValue.card.begin(); iter != NULL; iter = it->mValue.card.next(iter))
				{
					Json::Value leaf;
					leaf.append(iter->mValue.resourcestype);
					leaf.append(iter->mValue.subtype);
					leaf.append(iter->mValue.num);
					son["card"].append(leaf);
				}
				root["cards"].append(son);
			}		

			for(List<Goods>::Iter * iter = monsterDropList.begin(); iter != NULL; iter = monsterDropList.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["monsterDropList"].append(son);
			}

			for(List<Goods>::Iter * iter = fixedList.begin(); iter != NULL; iter = fixedList.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["fixedList"].append(son);
			}

			for(List<Goods>::Iter * iter = cost.begin(); iter != NULL; iter = cost.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["cost"].append(son);
			}


			for (List<UInt32>::Iter *iter = foodList.begin();iter != NULL; iter = foodList.next(iter))
			{
				root["foodList"].append(iter->mValue);
			}

			

			for(List<Goods>::Iter * iter = ends.begin(); iter != NULL; iter = ends.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["ends"].append(son);
			}

			root["allAttr"] = Json::Value(allAttr);

			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};


	struct WelfareMarket
	{
		UInt32 id;//����
		UInt32 difficulty;//����������Ѷ�		
		UInt32 finishTimes;//����ɴ���
		UInt32 maxTimes;//����ɴ���
		UInt32 times;//��������
	};
	struct WelfareResp	
	{
		List<WelfareMarket> welfaleMarket;//�и���������

		std::string convertDataToJson()
		{
			Json::Value root; 
			for(List<WelfareMarket>::Iter *it = welfaleMarket.begin();it!=NULL;it= welfaleMarket.next(it))
			{
				Json::Value son; 
				son["id "] = Json::Value(it->mValue.id );
				son["difficulty"] = Json::Value(it->mValue.difficulty);				
				son["finishTimes"] = Json::Value(it->mValue.finishTimes);
				son["maxTimes"] = Json::Value(it->mValue.maxTimes);
				son["times"] = Json::Value(it->mValue.times);
				root["welfaleMarket"].append(son);
			}		

			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};
	struct CGWelfareBegin
	{
		CGWelfareBegin(): id (0),difficulty (0){}

		UInt32 id;//����
		UInt32 difficulty;//�Ѷ�
		
		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{
				id  = root["id"].asUInt();	
				difficulty  = root["difficulty"].asUInt();
			}			
		}
		LYNX_MESSAGE_1(WELFALE_MARKET_BEGIN_REQ, CGWelfareBegin,std::string, jsonStr);
	};
	struct WelfareBeginResp	
	{
		WelfareBeginResp(): id (0),difficulty (0),result (0){}

		UInt32 id;//����
		UInt32 difficulty;//�Ѷ�
		UInt32 result;//���

		std::string convertDataToJson()
		{
			Json::Value root;     	
			root["id"] = Json::Value(id );
			root["difficulty"] = Json::Value(difficulty);
			root["result"] = Json::Value(result);

			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};
	struct CGWelfareEnd
	{
		CGWelfareEnd(): doType(0),id(0),difficulty(0){}
	
		UInt32 doType;//0ɨ�� 1�����ս 2��ս��;�뿪 3��սʧ��
		UInt32 id;//����
		UInt32 difficulty;
		std::string jsonStr;
		void convertJsonToData(std::string jsonStr)
		{
			Json::Reader reader;    
			Json::Value root;    
			if (reader.parse(jsonStr, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��      
			{
				doType  = root["doType"].asUInt();	
				id  = root["id"].asUInt();
				difficulty  = root["difficulty"].asUInt();
			}			
		}
		LYNX_MESSAGE_1(WELFALE_MARKET_END_REQ, CGWelfareEnd,std::string, jsonStr);
	};
	struct WelfareEndResp	
	{
		WelfareEndResp(): id(0),doType(0),difficulty(0),result(0){}

		UInt32 id;//����
		UInt32 doType;//0ɨ�� 1�����ս 2��ս��;�뿪 3��սʧ��
		UInt32 difficulty;
		UInt32 result;//
		UInt32 chaiCount;
		UInt32 miCount;
		UInt32 youCount;
		UInt32 yanCount;


		List<Award> awards;
		List<Goods> cost;
		List<Card> cards;
		List<Goods> monsterDropList;
		List<Goods> fixedList;
		List<Goods> ends;



		std::string convertDataToJson()
		{
			Json::Value root;   
			
			root["id"] = Json::Value(id );
			root["doType"] = Json::Value(doType );		
			root["difficulty"] = Json::Value(difficulty);
			root["result"] = Json::Value(result);
			root["chaiCount"] = Json::Value(chaiCount);
			root["miCount"] = Json::Value(miCount);
			root["youCount"] = Json::Value(youCount);
			root["yanCount"] = Json::Value(yanCount);

			Json::Value son; 
			for(List<Award>::Iter * it = awards.begin(); it != NULL; it = awards.next(it))			
			{
				Json::Value son;
				for(List<Goods>::Iter * iter = it->mValue.award.begin(); iter != NULL; iter = it->mValue.award.next(iter))
				{
					Json::Value leaf;
					leaf.append(iter->mValue.resourcestype);
					leaf.append(iter->mValue.subtype);
					leaf.append(iter->mValue.num);

					son["award"].append(leaf);
				}
				root["awards"].append(son);
			}

			for(List<Card>::Iter * it = cards.begin(); it != NULL; it = cards.next(it))			
			{
				Json::Value son;
				for(List<Goods>::Iter * iter = it->mValue.card.begin(); iter != NULL; iter = it->mValue.card.next(iter))
				{
					Json::Value leaf;
					leaf.append(iter->mValue.resourcestype);
					leaf.append(iter->mValue.subtype);
					leaf.append(iter->mValue.num);
					son["card"].append(leaf);
				}
				root["cards"].append(son);
			}		

			for(List<Goods>::Iter * iter = monsterDropList.begin(); iter != NULL; iter = monsterDropList.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["monsterDropList"].append(son);
			}

			for(List<Goods>::Iter * iter = cost.begin(); iter != NULL; iter = cost.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["cost"].append(son);
			}

			// 			for (List<UInt32>::Iter *iter = foodList.begin();iter != NULL; iter = foodList.next(iter))
			// 			{
			// 				root["foodList"].append(iter->mValue);
			// 			}

			for(List<Goods>::Iter * iter = fixedList.begin(); iter != NULL; iter = fixedList.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["fixedList"].append(son);
			}

			for(List<Goods>::Iter * iter = ends.begin(); iter != NULL; iter = ends.next(iter))
			{
				Json::Value son;	
				son.append(iter->mValue.resourcestype);
				son.append(iter->mValue.subtype);
				son.append(iter->mValue.num);
				root["ends"].append(son);
			}
			Json::FastWriter writer;  
			std::string strWrite = writer.write(root);
			return strWrite;
		}
	};

	class FireConfirmManager: public Singleton<FireConfirmManager>
	{
	public:
		FireConfirmManager();
		virtual ~FireConfirmManager();

		bool initial(Player* player);

		void release();

		void ChoiseNFromEnum(UInt32 num  ,UInt32 maxnum,List<UInt32> &OutList);		

		UInt32 GetConfirmTimes(UInt32 ConfirmLevel);

		void UpdataConfirmLevel(ConnId connId,bool flag);

		void SendFireConfirmCondition(const ConnId& connId);

		UInt32 CheckCopyFinishTime(Player* player);

		void SetCopyStart(Player* player,UInt32 CopyID);

		static void onConfirmDataReq(const  ConnId& , CGConfirmDataReq& );

		void ConfirmDataReq(const ConnId& connId, CGConfirmDataReq& msg);

		void SendForbiddenLogin(const ConnId& connId);

		void updateFireConfirmData(const ConnId& connId);

		
		static void onStartCopy(const  ConnId& ,CGChapterStart & );		//��ս�ؿ�

		static void onLeaveCopy(const  ConnId& , CGChapterLeave& );		//�뿪�ؿ�

		static void onEndCopy(const  ConnId& , CGChapterEnd & );		//�ؿ����� 

		static void onRelive(const  ConnId& , CGRelive & );		//����

	    static void onisRecieve(const  ConnId& connId, CGisRecievedReq & msg);

		static void onChapterAwardCard(const  ConnId& ,CGChapterAwardCard & );		//����

		static void onStageMopUp(const  ConnId& ,CGStageMopUp & );		//�ؿ�ɨ��
		
		void getAwardOnce(const  ConnId& connId,UInt32 copyID);//ɨ��һ�λ�ȡ����

		
		void foodGain(const  ConnId& connId, UInt32 foodType);//��ʳ�����ӳ�
		

		void getChapterCounter(const  ConnId& connId);//��ȡ�ؿ�����

		void saveAndGetResult(const  ConnId& connId,ChapterEndResp &resp,UInt32 fanPaiType);

		static void onFoodsReq(const  ConnId&  ,CGFoods & );

		void getfoods(UInt32 num,List<UInt32> &foods);//��ȡ���ֵ

		static void onStrengthReq(const  ConnId&  ,CGStrength & );

		void onStageSaodangReq(const  ConnId&  ,CGFoods &);//ɨ��



		static void onWelfaleBeginReq(const  ConnId&  ,CGWelfareBegin & );
		static void onWelfaleEndReq(const  ConnId&  ,CGWelfareEnd & );

		UInt32 refreshgetStrength(const ConnId& connId);//ˢ�²���ȡ����

		UInt32 getBuyStrengthPrice(Guid playerID,UInt32 nowBuyTimes,UInt32 &cost,UInt32 &num);//��ȡ���������۸�

		UInt32 getBuyCoinPrice(Guid playerID,UInt32 nowBuyTimes,UInt32 &cost,UInt32 &num);


		
	private:

		PlayerFireConfirmData FireConfirmData;
	};

	enum ConfirmErrorTimes
	{
		CONFIRM_LEVEL1_ERROR_TIMES	=1,//��صȼ���Ӧ���������״���
		CONFIRM_LEVEL2_ERROR_TIMES	=3,
		CONFIRM_LEVEL3_SEND_MAIL	=5,
		CONFIRM_LEVEL3_FORBID_LOGIN =10,
		CONFIRM_LEVEL_RESTET_TIMES  =50,
	};
	enum ConfirmNeedNum
	{
		CONFIRM_LEVEL1_NEED_NUM	=2,//��صȼ���Ӧ�ļ�ظ���
		CONFIRM_LEVEL2_NEED_NUM	=5,
		CONFIRM_LEVEL3_NEED_NUM	=10,

	};
	enum Confirm_Level
	{
		CONFIRM_LEVEL1=1,//��صȼ� 3���ȼ�
		CONFIRM_LEVEL2=2,
		CONFIRM_LEVEL3=3,
	};
	enum ConfirmCondition
	{
		//�ƶ��ٶȡ������ٶȡ�����CD�������˺��������ʡ������˺����ֵ�����ܷ�Χ��λ�õ㡢HP��MP��SP��buff����������ʱ��
		CONFIRM_SPEED							=0,
		CONFIRM_ATTACK_RATE						=1,
		CONFIRM_SKILL_CD						=2,
		CONFIRM_SKILL_DAMAGE					=3,
		CONFIRM_CRITICAL_STRIKE_RATE			=4, //������
		CONFIRM_CRITICAL_STRIKE_MAX_DAMAGE		=5,//�����˺����ֵ
		CONFIRM_SKILL_RANGE						=6,
		CONFIRM_POS								=7,//λ�õ�
		CONFIRM_HP								=8,
		CONFIRM_MP								=9,
		CONFIRM_SP								=10,
		CONFIRM_BUFFER							=11,

		CONFIRM_MAX								=12,
	};

	
}
#endif // __LYNX_GAME_SERVER_GAME_MANAGER_FIRE_CONFIRM_MANAGER_H__