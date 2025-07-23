#pragma once

#include <string>
#include <map>

#include "common/nndef.h"
#include "utils/tarslog.h"
#include "context/shlock.h"

using namespace nndef;
using namespace nnuser;
using namespace nncard;
using namespace nninvalid;
using namespace shstd;
using namespace lock;

namespace game
{
    namespace context
    {
        class User
        {
            //
            friend class Context;
        public:
            //User下注
            struct UserBetItem
            {
                int iIdlerID;
                map<long, int> mapBetInfo;
                UserBetItem(){
                    clear();
                }
                void clear()
                {
                    iIdlerID = 0;
                    mapBetInfo.clear();
                }
            };
        public:
            // 玩家下注信息
            struct UserBetInfo
            {
                long betAmount;              // 筹码总值                  
                map<int, int> mBetInfo;      // key 筹码下标 value 数量
                UserBetInfo()
                {
                    clear();
                }
                void clear()
                {
                    betAmount = 0;
                    mBetInfo.clear();
                }
            };

        private:
            User();

        public:
            explicit User(guid_t uid);
            ~User();

        public:
            void roundInit();

        public:
            guid_t getUid() const
            {
                return _uid;
            }
            cid_t getCid() const
            {
                return _cid;
            }
            void setCid(cid_t cid)
            {
                _cid = cid;
            }
            bool isRobot() const
            {
                return false;
            }

            void setNetBroken(bool netbroken)
            {
                _netbroken = netbroken;
            }
            bool isNetBroken() const
            {
                return _netbroken;
            }

            void setLeft(bool left) 
            {
                _left = left;
            }
            bool isLeft() const
            {
                return _left;
            }

            void setPreLeft(bool preleft) 
            {
                _preleft = preleft;
            }

            void setGender(int gender)
            {
                _gender = gender;
            }
            int getGender() const
            {
                return _gender;
            }

            void setNick(std::string nick)
            {
                _nick = nick;
            }
            std::string getNick() const
            {
                return _nick;
            }

            void setUrl(std::string url)
            {
                _url = url;
            }
            std::string getUrl() const
            {
                return _url;
            }

            void addIdler()
            {
                if (_betValue == 0)
                {
                    _idler++;
                }
                else
                {
                    _idler = 0;
                }
            }
            int getIdler()
            {
                return _idler;
            }

            void setWealth(long wealth)
            {
                _wealth = (wealth < 0 ? 0 : wealth);
            }
            long getWealth() const
            {
                return _wealth;
            }

            void setCoin(long value)
            {
                _coin = (value < 0 ? 0 : value);
            }
            long getCoin()
            {
                return _coin;
            }

            void setChange(long value)
            {
                _change = value;
            }
            long getChange()
            {
                return _change;
            }

            void setBetValue(long value)
            {
                _betValue = value;
            }

            long getBetValue()
            {
                return _betValue;
            }

            void setPayValue(long value)
            {
                _payValue = value;
            }

            long getPayValue()
            {
                return _payValue;
            }

            void setFeeValue(long value)
            {
                _feeValue = value;
            }

            long getFeeValue()
            {
                return _feeValue;
            }

            void setWinsBetsValue(long value)
            {
                _winsBetsValue = value;
            }
            long getWinsBetsValue()
            {
                return _winsBetsValue;
            }

            void setBetType(int value)
            {
                _betType = value;
            }
            int getBetType()
            {
                return _betType;
            }

            // 下面函数无用
            void setGameBeginWealth()
            {
                _game_begin_wealth = _wealth;
            }

            long getGameBeginWealth()
            {
                return _game_begin_wealth;
            }

            void addIdlerBetNum(int iIdlerID, long betNum);

            std::vector<UserBetItem> const & getIdlerBetNum() const
            {
                return vec_user_bet_info;
            }

            long getIdlerCurBetNum();

            long getIdlerBetNumByID(int iIdlerID);

            map<long, int> getIdlerBetNumMapByID(int iIdlerID);

            std::vector<UserBetItem> const & getLastIdlerBetNum() const
            {
                return vec_last_user_bet_info;
            }

            void addIdlerWinNum(int iIdlerID, long winNum);

            std::map<int, long> const & getIdlerWinNum() const
            {
                return _idler_winnum;
            }

            long getGameWinNum();

            long getGameBetNum();

            void setSettledNum(long value)
            {
                _settled_num += value;
            }

        public:
            void pushUserBetInfo(int iAreaID, int iIndex, long lValue);
            void pushUserBetInfoTwo(int iAreaID, int iIndex, long lValue, int iCount);
            long getUserBetInfo(int iAreaID);
            void copyUserBetInfo();
            void pushUserLastBetInfo(int iAreaID, int iIndex, int iCount);
            void pushUserLastBetAmount(int iAreaID, long lValue);
            long getUserLastBetInfo(int iAreaID);
            long getUserLastBetInfoAllAmount();
        public:
            std::map<int, UserBetInfo> const &getMapUserBetInfo() const
            {
                return _map_user_bet_info;
            }
            std::map<int, UserBetInfo> const &getMapUserLastBetInfo() const
            {
                return _map_user_last_bet_info;
            }
            void pushBetValue(int iAreaID, long lValue)
            {
                _map_area_bet.insert(make_pair(iAreaID, lValue));
            }
            std::map<int, long> const &getMapBetValue() const
            {
                return _map_area_bet;
            }
            void pushPayValue(int iAreaID, long lValue)
            {
                _map_area_pay.insert(make_pair(iAreaID, lValue));
            }
            std::map<int, long> const &getMapPayValue() const
            {
                return _map_area_pay;
            }
        protected:
            //guid_t          _uid;   //uid
            cid_t           _cid;   //位置id
            //bool            _robot; //是否机器人
            //std::string     _nick;  //玩家昵称
            //std::string     _url;   //玩家头像url
            bool            _netbroken; //掉线标记
            //bool            _left;      //离开
            //int             _gender;    //性别
            //long            _wealth;            //玩家财富(金币)
            long            _game_begin_wealth; //牌局开始筹码
        

            std::vector<UserBetItem> vec_user_bet_info;//闲家区域下注
            std::vector<UserBetItem> vec_last_user_bet_info;//上次闲家区域下注
            std::map<int, long> _idler_winnum; //闲家区域赢取筹码
            bool            _preleft;//是否离开过

            long            _settled_num;//已经扣除过

            //CMutex _idler_betnum_mutex;
        protected:
            guid_t _uid;         // uid
            std::string _nick;   // 玩家昵称
            std::string _url;    // 玩家头像url
            bool _left;          // 离开
            int _gender;         // 性别
            int _idler;          // 连续多少手未下注
            long _wealth;        // 玩家财富(好像没什么)
            long _coin;          // 筹码
            long _change;        // 筹码改变 + 赢 - 输
            long _betValue;      // 总下注
            long _payValue;      // 总赔付
            long _feeValue;      // 总抽水
            long _winsBetsValue; // 赔付区域的总下注
            int _betType;        // 下注类型 0 正常 1 复投 2 倍投
            std::map<int, UserBetInfo> _map_user_bet_info;        // 区域下注 key 区域下标 value 下注信息
            std::map<int, UserBetInfo> _map_user_last_bet_info;   // 上局区域下注 key 区域下标 value 下注信息
            std::map<int, long> _map_area_bet;                    // 区域总下注(结算用)
            std::map<int, long> _map_area_pay;                    // 区域总赔付(结算用)
        };
    };
};

