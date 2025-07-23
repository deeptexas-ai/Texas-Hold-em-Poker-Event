#pragma once

#include <map>

#include "common/nndef.h"
#include "context/user.h"
#include "context/shlock.h"

//
using namespace nndef;
using namespace nnuser;
using namespace shstd;
using namespace lock;

namespace game
{
    class GameRoot;

    namespace context
    {
        struct sCardsInfo
        {
            int rank;
            E_NN_TYPE card_type;;
            vecc_t cards;
            sCardsInfo(){
                rank = -1;
                card_type = NN_TYPE_NN_NONE;
                cards.clear();
            }
        };

        struct sAreaBetInfo
        {
            long betAmount;              // 总下注
            std::map<int, int> mBetInfo; // key 筹码下标 value 筹码数量
            sAreaBetInfo()
            {
                betAmount = 0;
                mBetInfo.clear();
            }
        };
        //
        class Context
        {
            DISALLOW_COPY_AND_ASSIGN(Context)
        private:
            Context();
            explicit Context(GameRoot *root);

        public:
            //
            static Context *Create(GameRoot *root)
            {
                return new Context(root);
            }
            //
            void gameInit();
            //
            void roundInit();
            //
            void createAreaID();
            //
            inline GameRoot const *getRoot()
            {
                return _root;
            }

            inline void setBalance(long value)
            {
                _balance = value;
            }

            inline long const &getBalance() const
            {
                return _balance;
            }
            inline int const &getRound() const
            {
                return _round;
            }

            inline vecc_t const &getVecWallCard() const
            {
                return _wallcards;
            }
            //
            inline vecc_t &refVecWallCard()
            {
                return _wallcards;
            }

            inline vecc_t const &getVecBoyCard() const
            {
                return _boycards;
            }
            //
            inline vecc_t &refVecBoyCard()
            {
                return _boycards;
            }

            inline vecc_t const &getVecGirlCard() const
            {
                return _girlcards;
            }
            //
            inline vecc_t &refVecGirlCard()
            {
                return _girlcards;
            }

            inline vecc_t const &getVecCommCard() const
            {
                return _commcards;
            }
            //
            inline vecc_t &refVecCommCard()
            {
                return _commcards;
            }

            inline vecc_t const &getVecBoyWinCard() const
            {
                return _boywincards;
            }
            //
            inline vecc_t &refVecBoyWinCard()
            {
                return _boywincards;
            }

            inline vecc_t const &getVecGirlWinCard() const
            {
                return _girlwincards;
            }
            //
            inline vecc_t &refVecGirlWinCard()
            {
                return _girlwincards;
            }
        public:
            void setBoyHandType(E_NN_HAND_TYPE card_type)
            {
                _boyhandtype = card_type;
            }

            E_NN_HAND_TYPE getBoyHandType()
            {
                return _boyhandtype;
            }

            void setGirlHandType(E_NN_HAND_TYPE card_type)
            {
                _girlhandtype = card_type;
            }

            E_NN_HAND_TYPE getGirlHandType()
            {
                return _girlhandtype;
            }

            void setBoyCardType(E_NN_TYPE card_type)
            {
                _boycardstype = card_type;
            }

            E_NN_TYPE getBoyCardType()
            {
                return _boycardstype;
            }

            void setGirlCardType(E_NN_TYPE card_type)
            {
                _girlcardstype = card_type;
            }

            E_NN_TYPE getGirlCardType()
            {
                return _girlcardstype;
            }

            void setWinIndex(int value)
            {
                _winIndex = value;
            }
            int  getWinIndex()
            {
                return _winIndex;
            }

            void setDismiss(int value)
            {
                _dismiss = value;
            }
            int getDismiss()
            {
                return _dismiss;
            }

            void setNextTime(int value)
            {
                _nextTime = value;
            }

            int getNextTime()
            {
                return _nextTime;
            }

            void updatePairAIdle(bool clean)
            {
                if (clean)
                {
                    _pairAIdle = 0;
                }
                else
                {
                    _pairAIdle++;
                }
            }

            int getPairAIdle()
            {
                return _pairAIdle;
            }

            void updateHuluIdle(bool clean)
            {
                if (clean)
                {
                    _huluIdle = 0;
                }
                else
                {
                    _huluIdle++;
                }
            }

            int getHuluIdle()
            {
                return _huluIdle;
            }

            void updateKingIdle(bool clean)
            {
                if (clean)
                {
                    _kingIdle = 0;
                }
                else
                {
                    _kingIdle++;
                }
            }

            int getKingIdle()
            {
                return _kingIdle;
            }

            void pushWinCowBoy(int value)
            {
                _vWinCowBoy.push_back(value);
                if (_vWinCowBoy.size() > 300)
                {
                    _vWinCowBoy.pop_front();
                }
            }

            std::deque<int> const &getDequeWinCowBoy() const
            {
                return _vWinCowBoy;
            }

            void pushWinCardType(int value)
            {
                _vWinCardType.push_back(value);
                if (_vWinCardType.size() > 300)
                {
                    _vWinCardType.pop_front();
                }
            }

            std::deque<int> const &getDequeWinCardType() const
            {
                return _vWinCardType;
            }

            void pushCowBoy(int value)
            {
                _vCowBoy.push_back(value);
                if (_vCowBoy.size() > 6)
                {
                    _vCowBoy.pop_front();
                }
            }

            std::deque<int> const &getDequeCowBoy() const
            {
                return _vCowBoy;
            }

            void pushHandSame(int value)
            {
                _vHandSame.push_back(value);
                if (_vHandSame.size() > 25)
                {
                    _vHandSame.pop_front();
                }
            }

            std::deque<int> const &getDequeHandSame() const
            {
                return _vHandSame;
            }

            void pushHandPair(int value)
            {
                _vHandPair.push_back(value);
                if (_vHandPair.size() > 25)
                {
                    _vHandPair.pop_front();
                }
            }

            std::deque<int> const &getDequeHandPair() const
            {
                return _vHandPair;
            }

            void pushWinHight(int value)
            {
                _vWinHight.push_back(value);
                if (_vWinHight.size() > 12)
                {
                    _vWinHight.pop_front();
                }
            }

            std::deque<int> const &getDequeWinHight() const
            {
                return _vWinHight;
            }

            void pushWinTwoPair(int value)
            {
                _vWinTwoPair.push_back(value);
                if (_vWinTwoPair.size() > 12)
                {
                    _vWinTwoPair.pop_front();
                }
            }

            std::deque<int> const &getDequeWinTwoPair() const
            {
                return _vWinTwoPair;
            }

            void pushWinSame(int value)
            {
                _vWinSame.push_back(value);
                if (_vWinSame.size() > 15)
                {
                    _vWinSame.pop_front();
                }
            }

            std::deque<int> const &getDequeWinSame() const
            {
                return _vWinSame;
            }

            void pushAreaBetInfo(int iAreaID, int iIndex, long lValue, int iCount)
            {
                auto iter = _mAreaBetInfo.find(iAreaID);
                if (iter != _mAreaBetInfo.end())
                {
                    iter->second.betAmount += lValue;
                    iter->second.mBetInfo[iIndex] += iCount;
                }
                else
                {
                    sAreaBetInfo info;
                    info.betAmount = lValue;
                    info.mBetInfo.insert(make_pair(iIndex, iCount));

                    _mAreaBetInfo.insert(make_pair(iAreaID, info));
                }

                _maxTableBet += lValue;
            }

            std::map<int, sAreaBetInfo> const &getMapAreaBetInfo()
            {
                return _mAreaBetInfo;
            }

            void pushWinArea(int iAreaID)
            {
                _vWinArea.push_back(iAreaID);
            }

            std::vector<int> const &getVecWinArea()
            {
                return _vWinArea;
            }
            
            long getMaxTableBet()
            {
                return _maxTableBet;
            }
            // 统计牌局
            void addCowBoyWins()
            {
                _cowBoyWins++;
            }
            int getCowBoyWins()
            {
                return _cowBoyWins;
            }
            void addCowTieWins()
            {
                _cowTieWins++;
            }
            int getCowTieWins()
            {
                return _cowTieWins;
            }
            void addCowGirlWins()
            {
                _cowGirlWins++;
            }
            int getCowGirlWins()
            {
                return _cowGirlWins;
            }
            void addHandSameWins()
            {
                _handSameWins++;
            }
            int getHandSameWins()
            {
                return _handSameWins;
            }
            void addHandPairWins()
            {
                _handPairWins++;
            }
            int getHandPairWins()
            {
                return _handPairWins;
            }
            void addHandPairAWins()
            {
                _handPairAWins++;
            }
            int getHandPairAWins()
            {
                return _handPairAWins;
            }

            void addWinHightWins()
            {
                _winHightWins++;
            }
            int getWinHightWins()
            {
                return _winHightWins;
            }
            void addWinTwoPairsWins()
            {
                _winTwoPairsWins++;
            }
            int getWinTwoPairsWins()
            {
                return _winTwoPairsWins;
            }
            void addWinSameWins()
            {
                _winSameWins++;
            }
            int getWinSameWins()
            {
                return _winSameWins;
            }
            void addWinHuLuWins()
            {
                _winHuLuWins++;
            }
            int getWinHuLuWins()
            {
                return _winHuLuWins;
            }
            void addWinKingWins()
            {
                _winKingWins++;
            }
            int getWinKingWins()
            {
                return _winKingWins;
            }
            void setUserCount(int value)
            {
                _userCount = value;
            }
            int getUserCount()
            {
                return _userCount;
            }
            void setCreateID(long value)
            {
                _createID = value;
            }
            long getCreateID()
            {
                return _createID;
            }
            void setSpecialWinID(long value)
            {
                _specialWinID = value;
            }
            long getSpecialWinID()
            {
                return _specialWinID;
            }
            void setSpecialWinAmount(long value)
            {
                _specialWinAmount = value;
            }
            long getSpecialWinAmount()
            {
                return _specialWinAmount;
            }
            void setFees(long value)
            {
                _fees = value;
            }
            long getFees()
            {
                return _fees;
            }

            void setBankerBets(long value)
            {
                _lBankerBets = value;
            }
            long getBankerBets()
            {
                return _lBankerBets;
            }
            void setBankerPays(long value)
            {
                _lBankerPays = value;
            }
            long getBankerPays()
            {
                return _lBankerPays;
            }
            void setBankerFees(long value)
            {
                _lBankerFees = value;
            }
            long getBankerFees()
            {
                return _lBankerFees;
            }
            void setBankerChange(long value)
            {
                _lBankerChange = value;
            }
            long getBankerChange()
            {
                return _lBankerChange;
            }
            void pushBankerAreaBetInfo(int iAreaID, long lBet)
            {
                auto iter = _mBankerAreaBetInfo.find(iAreaID);
                if (iter != _mBankerAreaBetInfo.end())
                {
                    _mBankerAreaBetInfo[iAreaID] += lBet;
                }
                else
                {
                    _mBankerAreaBetInfo.insert(make_pair(iAreaID, lBet));
                }
            }
            std::map<int, long> const &getMapBankerAreaBetInfo()
            {
                return _mBankerAreaBetInfo;
            }
            long getBankerAreaBetInfo(int iAreaID)
            {
                auto iter = _mBankerAreaBetInfo.find(iAreaID);
                if (iter != _mBankerAreaBetInfo.end())
                {
                    return iter->second;
                }
                return 0;
            }
            void pushBankerAreaPayInfo(int iAreaID, long lPay)
            {
                auto iter = _mBankerAreaPayInfo.find(iAreaID);
                if (iter != _mBankerAreaPayInfo.end())
                {
                    _mBankerAreaPayInfo[iAreaID] += lPay;
                }
                else
                {
                    _mBankerAreaPayInfo.insert(make_pair(iAreaID, lPay));
                }
            }
            std::map<int, long> const &getMapBankerAreaPayInfo()
            {
                return _mBankerAreaPayInfo;
            }
            bool isExitMapBankerAreaPayInfo(int iAreaID)
            {
                auto iter = _mBankerAreaPayInfo.find(iAreaID);
                if (iter != _mBankerAreaPayInfo.end())
                {
                    return true;
                }
                return false;
            }

            long getBankerAreaPayInfo(int iAreaID)
            {
                auto iter = _mBankerAreaPayInfo.find(iAreaID);
                if (iter != _mBankerAreaPayInfo.end())
                {
                    return iter->second;
                }
                return 0;
            }
        public:
            inline vecc_t const &getVecBankerCard() const
            {
                return _bankercards;
            }
            //
            inline vecc_t &refVecBankerCard()
            {
                return _bankercards;
            }

            inline std::map<int, vecc_t> const &getVeIdlerCard() const
            {
                return _idlercards;
            }
            //
            inline std::map<int, vecc_t> &refVecIdlerCard()
            {
                return _idlercards;
            }

            inline std::vector<sCardsInfo> const &getVecAllCard() const
            {
                return _allcards;
            }
            //
            inline std::vector<sCardsInfo> &refVecAllCard()
            {
                return _allcards;
            }

            inline std::map<guid_t, User> const &getUserMap() const
            {
                return _uid_user_map;
            }
            //
            inline std::map<guid_t, User> &refUserMap()
            {
                return _uid_user_map;
            }
        public:
            //
            void addUser(guid_t uid, cid_t cid, bool robot = false);
            //
            void delUser(guid_t uid);

            cid_t getCidByUid(guid_t uid);
            //
            guid_t getUidByCid(cid_t cid);
            //
            User *getUserByUid(guid_t uid);
            //
            User *getUserByCid(cid_t cid);

            std::map<int, long> getIdlerBetNum();

            void addIdlerCalInfo(int idlerID, CalInfo& info, int maxRound);

            std::map<int, std::vector<CalInfo>> const & getIdlerCalInfo() const
            {
                /*CSafeMutex lock(_idler_calinfo_mutex);*/
                return _idler_calinfo;
            }

            std::map<int, CalInfo> const & getRoundIdlerCalInfo() const
            {
                return _round_idler_calinfo;
            }

            int getBankerAreaID() const
            {
                return _ibanker_areaid;
            }

            int getSelfAreaID() const
            {
                return _iself_areaid;
            }

            int getWatchAreaID() const
            {
                return _iwatch_areaid;
            }

            std::vector<int> const & getIdlerAreaID() const
            {
                return _vec_idler_areaid;
            }

            std::vector<std::vector<int>> const& getRankAllList() const
            {
                return _vec_rank_all_list;
            }

            void addIdlerBetNum(int idlerID, long lPlayerID,  std::map<long, int>& mapBetNum);

            std::map<int, std::vector<long>> const & getIdlerUidList() const
            {
                return _idler_uid_map;
            }

            long getIdlerBetNumByID(int idlerID);

            std::map<long, int> getIdlerBetNumMapByID(int iIdlerID);

            void setBankerCardType(E_NN_TYPE card_type)
            {
                _bankercardstype = card_type;
            }

            E_NN_TYPE getBankerCardType()
            {
                return _bankercardstype;
            }

            void setIdlerCardType(E_NN_TYPE card_type, int iIdlerID);
            
            E_NN_TYPE getIdlerCardType(int iIdlerID);
          
            void setProcessOptionTime()
            {
                _process_option_time = TNOW;
            }

            long getProcessOptionTime()
            {
                return _process_option_time;
            }

            void setBetLock(bool value)
            {
                _bet_lock = value;
            }

            bool getBetLock()
            {
                return _bet_lock;
            }

            void setControlLineType(int iType)
            {
                _control_line_type = iType;
            }   

            int getControlLineType()
            {
                return _control_line_type;
            }

            void setControlProfit(long value)
            {
                _cur_control_profit = value;
            }

            long getControlProfit()
            {   
                return _cur_control_profit;
            }

        private:
            //
            int nnrand(int max, int min = 0);

        protected:
            GameRoot *const _root;

            long _createID;                 // 庄家ID
            long _balance;                  // 庄家余额

            int _round;                      // 牌局数
            vecc_t _wallcards;               // 牌堆
            vecc_t _boycards;                // 牛仔手牌
            vecc_t _girlcards;               // 美女手牌
            vecc_t _commcards;               // 公共牌
            vecc_t _boywincards;             // 牛仔最终牌
            vecc_t _girlwincards;            // 美女最终牌
            E_NN_HAND_TYPE _boyhandtype;     // 牛仔手牌牌型
            E_NN_HAND_TYPE _girlhandtype;    // 美女手牌牌型
            E_NN_TYPE _boycardstype;         // 牛仔牌型
            E_NN_TYPE _girlcardstype;        // 美女牌型
            int _winIndex;                   // 赢家下标 101 牛仔 102 平局 103 美女
            int _dismiss;                    // 是否解散
            int _nextTime;                   // 当前状态结束时间戳
            int _pairAIdle;                  // 对A几手未出
            int _huluIdle;                   // 葫芦几手未出
            int _kingIdle;                   // 皇同几手未出
            std::deque<int> _vWinCowBoy;     // 牛仔平局美女101-102-103 <300条>走势图
            std::deque<int> _vWinCardType;   // 获取牌型走势图
            std::deque<int> _vCowBoy;        // 牛仔平局美女101-102-103 <6条>
            std::deque<int> _vHandSame;      // 任一人手牌 同花/连牌 1 出 2 未出 <25条>
            std::deque<int> _vHandPair;      // 任一人手牌 对子 1 出 2 未出 <25条>
            std::deque<int> _vWinHight;      // 获胜牌型 高牌/一对 <12条>
            std::deque<int> _vWinTwoPair;    // 获胜牌型 两对 <12条>
            std::deque<int> _vWinSame;       // 获胜牌型 三条/顺子/同花 <15条>

            std::vector<int> _vWinArea;                  // 击中区域
            std::map<int, sAreaBetInfo> _mAreaBetInfo;   // 区域下注
            std::map<guid_t, User> _uid_user_map;        // 玩家
            long _maxTableBet;                           // 桌面总下注额度 

            // 统计牌局
            // 胜负平
            int _cowBoyWins;        // 牛仔
            int _cowTieWins;        // 平局
            int _cowGirlWins;       // 美女
            // 任一人手牌
            int _handSameWins;      // 同花/连牌/同花连牌
            int _handPairWins;      // 对子
            int _handPairAWins;     // 对A
            // 获胜牌型
            int _winHightWins;      // 高牌/一对
            int _winTwoPairsWins;   // 两对
            int _winSameWins;       // 3条/顺子/同花
            int _winHuLuWins;       // 葫芦
            int _winKingWins;       // 金刚/同花顺/皇同

            int _userCount;   // 上局玩家总人数(如果结束时发现人数不一致就更新)

            long _specialWinID;       // 特殊区域获取玩家ID
            long _specialWinAmount;   // 特殊区域获取玩家赢的筹码
            long _fees;               // 抽水额度

            // 庄家信息
            long _lBankerBets;     // 当局总下注
            long _lBankerPays;     // 当局总赔付
            long _lBankerFees;     // 当局总抽水
            long _lBankerChange;   // 当局盈亏
            std::map<int, long> _mBankerAreaBetInfo;   // 当前区域总下注
            std::map<int, long> _mBankerAreaPayInfo;   // 当前区域总赔付 
            

            //下面的不要(有时间清理掉)
            vecc_t _bankercards;//庄家牌
            E_NN_TYPE _bankercardstype;// 庄家牌型
            std::map<int, vecc_t> _idlercards;// 闲家牌
            std::map<int, E_NN_TYPE> _idlercardstype;// 闲家牌型

            std::vector<sCardsInfo> _allcards; // 所有的牌

            int _ibanker_areaid;
            int _iself_areaid;
            int _iwatch_areaid;
            std::vector<int> _vec_idler_areaid;
            std::vector<std::vector<int>> _vec_rank_all_list;
            std::vector<std::vector<int>> _vec_rank_allwin_list;
            std::vector<std::vector<int>> _vec_rank_alllost_list;
            std::vector<std::vector<int>> _vec_rank_other_list;

            std::map<int, std::vector<CalInfo>> _idler_calinfo;//历史
            std::map<int, CalInfo> _round_idler_calinfo;//本局

            std::map<int, std::vector<long>> _idler_uid_map;

            long _process_option_time;//操作时间

            bool  _bet_lock; //下注锁

            int _control_line_type;//控牌标志
            long _cur_control_profit;//当前收益 

            CMutex _uid_user_map_mutex;
            CMutex _idler_calinfo_mutex;
            CMutex _idler_uid_map_mutex;
        };
    };
};

