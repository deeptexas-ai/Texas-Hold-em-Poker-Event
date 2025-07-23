#include "context/user.h"
#include "utils/tarslog.h"

namespace game
{
    namespace context
    {
        User::User()
            : _uid(nil_uid)
            , _nick("")
            , _url("")
            , _left(false)
            , _gender(0)
            , _idler(0)
            , _wealth(0)
            , _coin(0)
        {
            roundInit();
        }

        User::User(guid_t uid)
            : _uid(uid)
            , _nick("")
            , _url("")
            , _left(false)
            , _gender(0)
            , _idler(0)
            , _wealth(0)
            , _coin(0)
        {
            for(auto& item : this->_map_user_last_bet_info)
            {
                item.second.clear();
            }
            this->_map_user_last_bet_info.clear();
            for(auto& item : this->_map_user_bet_info)
            {
                item.second.clear();
            }
            this->_map_user_bet_info.clear();
            roundInit();
        }

        void User::roundInit()
        {
            copyUserBetInfo();

            for(auto& item : this->_map_user_bet_info)
            {
                item.second.clear();
            }
            this->_map_user_bet_info.clear();

            this->_map_area_bet.clear();
            this->_map_area_pay.clear();

            //
            for(auto& item : this->vec_last_user_bet_info)
            {
                item.clear();
            }
            for(auto& item : this->vec_user_bet_info)
            {
                this->vec_last_user_bet_info.push_back(item);
                item.clear();
            }

            this->_change = 0;
            this->_betValue = 0;
            this->_payValue = 0;
            this->_feeValue = 0;
            this->_winsBetsValue = 0;
            
            this->vec_user_bet_info.clear();
            this->_idler_winnum.clear();

            this->_preleft = false;
            this->_settled_num = 0;

            this->_game_begin_wealth = _wealth;
        }

        User::~User()
        {
        }

        void User::addIdlerBetNum(int iIdlerID, long betNum)
        {
            //CSafeMutex lock( _idler_betnum_mutex);
            _wealth -= betNum;
            //
            for(auto& item : vec_user_bet_info)
            {
                if(item.iIdlerID == iIdlerID)
                {
                    auto it = item.mapBetInfo.find(betNum);
                    if(it == item.mapBetInfo.end())
                    {
                        item.mapBetInfo.insert(std::make_pair(betNum, 1));
                    }
                    else
                    {
                        it->second += 1;
                    }
                    return;
                }
            }
            UserBetItem info;
            info.iIdlerID = iIdlerID;
            info.mapBetInfo.insert(std::make_pair(betNum, 1));
            vec_user_bet_info.push_back(info);
        }

        long User::getIdlerCurBetNum()
        {
            //CSafeMutex lock( _idler_betnum_mutex);
            long idler_betnum = 0;
            for(auto& item : vec_user_bet_info)
            {
                for(auto sub : item.mapBetInfo)
                {
                    idler_betnum += (sub.first * sub.second);
                }
            }
            return idler_betnum;
        }

        long User::getIdlerBetNumByID(int iIdlerID)
        {
            //CSafeMutex lock( _idler_betnum_mutex);
            long idler_betnum = 0;
            for(auto& item : vec_user_bet_info)
            {
                if(item.iIdlerID != iIdlerID)
                {
                    continue;
                }
                for(auto sub : item.mapBetInfo)
                {
                    idler_betnum += (sub.first * sub.second);
                }
            }
            return idler_betnum;
        }

        map<long, int> User::getIdlerBetNumMapByID(int iIdlerID)
        {
            //CSafeMutex lock( _idler_betnum_mutex);
            map<long, int> idler_betnum_map;
            for(auto& item : vec_user_bet_info)
            {
                if(item.iIdlerID != iIdlerID)
                {
                    continue;
                }

                for(auto sub : item.mapBetInfo)
                {
                    idler_betnum_map.insert(std::make_pair(sub.first, sub.second));
                }
            }

            return std::move(idler_betnum_map);
        }

        void User::addIdlerWinNum(int iIdlerID, long winNum)
        {
            auto it = _idler_winnum.find(iIdlerID);
            if(it == _idler_winnum.end())
            {
                _idler_winnum.insert(std::make_pair(iIdlerID, winNum));
            }
            else
            {
                it->second += winNum;
            }
        }

        long User::getGameWinNum()
        {
            //CSafeMutex lock( _idler_betnum_mutex);
            long total_bet_num = 0;
            long total_win_num = 0;

            for(auto& item : vec_user_bet_info)
            {
                for(auto sub : item.mapBetInfo)
                {
                    total_bet_num += (sub.first * sub.second);
                }
            }

            for(auto item : _idler_winnum)
            {
                total_win_num += item.second;
            }
            return _preleft ? total_win_num : (total_win_num - total_bet_num);
        }

        long User::getGameBetNum()
        {
            //CSafeMutex lock( _idler_betnum_mutex);
            long total_bet_num = 0;
            for(auto& item : vec_user_bet_info)
            {
                for(auto sub : item.mapBetInfo)
                {
                    total_bet_num += (sub.first * sub.second);
                }
            }
            return total_bet_num < _settled_num ? 0 : (total_bet_num - _settled_num);
        }

        void User::pushUserBetInfo(int iAreaID, int iIndex, long lValue)
        {
            auto iter = _map_user_bet_info.find(iAreaID);
            if (iter != _map_user_bet_info.end())
            {
                iter->second.betAmount += lValue;
                iter->second.mBetInfo[iIndex] += 1;
            }
            else
            {
                UserBetInfo info;
                info.betAmount = lValue;;
                info.mBetInfo.insert(make_pair(iIndex, 1));

                _map_user_bet_info.insert(make_pair(iAreaID, info));
            }
        }

        void User::pushUserBetInfoTwo(int iAreaID, int iIndex, long lValue, int iCount)
        {
            auto iter = _map_user_bet_info.find(iAreaID);
            if (iter != _map_user_bet_info.end())
            {
                iter->second.betAmount += lValue;
                iter->second.mBetInfo[iIndex] += iCount;
            }
            else
            {
                UserBetInfo info;
                info.betAmount = lValue;;
                info.mBetInfo.insert(make_pair(iIndex, iCount));

                _map_user_bet_info.insert(make_pair(iAreaID, info));
            }
        }

        long User::getUserBetInfo(int iAreaID)
        {
            auto iter = _map_user_bet_info.find(iAreaID);
            if (iter != _map_user_bet_info.end())
            {
                return iter->second.betAmount;
            }
            return 0;
        }

        void User::copyUserBetInfo()
        {
            // 如果当局有下注,则更新复投列表
            if (_map_user_bet_info.size() > 0)
            {
                for(auto& item : this->_map_user_last_bet_info)
                {
                    item.second.clear();
                }
                _map_user_last_bet_info.clear();

                setBetType(1);

                for (auto iter : _map_user_bet_info)
                {
                    for (auto iiter : iter.second.mBetInfo)
                    {
                        pushUserLastBetInfo(iter.first, iiter.first, iiter.second);
                    }
                    pushUserLastBetAmount(iter.first, iter.second.betAmount);
                }
            }
            else
            {
                if (_map_user_last_bet_info.size() > 0)
                {
                    setBetType(1);
                }
                else
                {
                    setBetType(0);
                }
            }
        }

        void User::pushUserLastBetInfo(int iAreaID, int iIndex, int iCount)
        {
            auto iter = _map_user_last_bet_info.find(iAreaID);
            if (iter != _map_user_last_bet_info.end())
            {
                iter->second.mBetInfo[iIndex] += iCount;
            }
            else
            {
                UserBetInfo info;
                info.betAmount = 0;;
                info.mBetInfo.insert(make_pair(iIndex, iCount));

                _map_user_last_bet_info.insert(make_pair(iAreaID, info));
            }
        }

        void User::pushUserLastBetAmount(int iAreaID, long lValue)
        {
            auto iter = _map_user_last_bet_info.find(iAreaID);
            if (iter != _map_user_last_bet_info.end())
            {
                iter->second.betAmount += lValue;
            }
        }

        long User::getUserLastBetInfo(int iAreaID)
        {
            auto iter = _map_user_last_bet_info.find(iAreaID);
            if (iter != _map_user_last_bet_info.end())
            {
                return iter->second.betAmount;
            }
            return 0;
        }

        long User::getUserLastBetInfoAllAmount()
        {
            long lAllValue = 0;
            for (auto iter : _map_user_last_bet_info)
            {
                lAllValue += iter.second.betAmount;
            }
            return lAllValue;
        }
    };
};
