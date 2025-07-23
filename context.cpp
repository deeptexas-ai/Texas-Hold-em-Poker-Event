#include "common/macros.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include <algorithm>

namespace game
{
    namespace context
    {
        Context::Context() : _root(NULL)
        {
            LOG_FATAL("creator Context without root.");
        }

        Context::Context(GameRoot *root) : _root(root)
        {
            gameInit();
        }

        void Context::gameInit()
        {
            _uid_user_map.clear();
            _idler_calinfo.clear();

            _pairAIdle = 0;
            _huluIdle = 0;
            _kingIdle = 0;

            _vWinCowBoy.clear();
            _vWinCardType.clear();
            _vCowBoy.clear();
            _vHandSame.clear();
            _vHandPair.clear();
            _vWinHight.clear();
            _vWinTwoPair.clear();
            _vWinSame.clear();

            _cowBoyWins = 0;
            _cowTieWins = 0;
            _cowGirlWins = 0;

            _handSameWins = 0;
            _handPairWins = 0;
            _handPairAWins = 0;

            _winHightWins = 0;
            _winTwoPairsWins = 0;
            _winSameWins = 0;
            _winHuLuWins = 0;
            _winKingWins = 0;

            _dismiss = 0;
            _round = 0;
            _userCount = 0;
            _balance = 0;
            _specialWinID = 0;
            _specialWinAmount = 0;
            _fees = 0;

            _lBankerBets = 0;
            _lBankerPays = 0;
            _lBankerFees = 0;
            _lBankerChange = 0;
            _mBankerAreaBetInfo.clear();
            _mBankerAreaPayInfo.clear();

            createAreaID();
            roundInit();
        }

        void Context::roundInit()
        {
            this->_round++;

            this->_wallcards.clear();
            this->_boycards.clear();
            this->_girlcards.clear();
            this->_commcards.clear();
            this->_boywincards.clear();
            this->_girlwincards.clear();
            this->_boyhandtype = NN_HAND_TYPE_NN_N0;
            this->_girlhandtype = NN_HAND_TYPE_NN_N0;
            this->_boycardstype = NN_TYPE_NN_N0;
            this->_girlcardstype = NN_TYPE_NN_N0;

            this->_winIndex = 0;
            this->_mAreaBetInfo.clear();
            this->_maxTableBet = 0;
            this->_vWinArea.clear();

            this->_specialWinID = 0;
            this->_specialWinAmount = 0;
            this->_fees = 0;

            this->_lBankerBets = 0;
            this->_lBankerPays = 0;
            this->_lBankerFees = 0;
            this->_lBankerChange = 0;
            this->_mBankerAreaBetInfo.clear();
            this->_mBankerAreaPayInfo.clear();

            this->_bankercards.clear();
            this->_idlercards.clear();
            this->_allcards.clear();
            this->_round_idler_calinfo.clear();
            this->_idler_uid_map.clear();
            this->_idlercardstype.clear();
            this->_bankercardstype = NN_TYPE_NN_NONE;
            this->_process_option_time = 0;
            this->_bet_lock = false;
            this->_control_line_type = false;
            for (auto it = _uid_user_map.begin(); it != _uid_user_map.end(); it++)
            {
                // 设置连续未下注次数
                it->second.addIdler();
                // 初始化轮回数据
                it->second.roundInit();
            }

            srand(TNOW);
            _vec_rank_all_list.clear();
            _vec_rank_all_list.insert(_vec_rank_all_list.begin(), _vec_rank_other_list.begin(), _vec_rank_other_list.end());
            _vec_rank_all_list.push_back(_vec_rank_allwin_list[rand() % _vec_rank_allwin_list.size()]);
            _vec_rank_all_list.push_back(_vec_rank_alllost_list[rand() % _vec_rank_alllost_list.size()]);
        }

        void Context::createAreaID()
        {
            _ibanker_areaid = NN_AREAID_BANKER * 1000;
            _iself_areaid = NN_AREAID_SELF * 1000;
            _iwatch_areaid = NN_AREAID_WATCH * 1000;
            std::vector<int> areaid_list;
            areaid_list.push_back(NN_AREAID_BANKER * 1000);
            for(int i = 0; i < 4; i++)
            {
                _vec_idler_areaid.push_back(NN_AREAID_IDLER * 1000 + i);
            }

            // 获取所有排列组合
            vector<int> vec_rank_list = {0, 1, 2, 3, 4};
            _vec_rank_allwin_list.clear();
            _vec_rank_alllost_list.clear();
            _vec_rank_other_list.clear();
            
            do{
                if(vec_rank_list[0] == 0)
                {
                    _vec_rank_allwin_list.push_back(vec_rank_list);
                }
                else if(vec_rank_list[0] == 4)
                {
                    _vec_rank_alllost_list.push_back(vec_rank_list);
                }
                else
                {
                    _vec_rank_other_list.push_back(vec_rank_list);
                }
            }while(next_permutation(vec_rank_list.begin(), vec_rank_list.end()));
        }

        void Context::addUser(guid_t uid, cid_t cid, bool robot)
        {
            CSafeMutex lock(_uid_user_map_mutex);
            auto it = _uid_user_map.find(uid);
            if (it != _uid_user_map.end())
            {
                DLOG_TRACE("user is exist, uid = " << uid);
                return;
            }

            _uid_user_map.insert(std::make_pair(uid, User(uid)));
        }

        void Context::delUser(guid_t uid)
        {
            CSafeMutex lock(_uid_user_map_mutex);
            auto it = _uid_user_map.find(uid);
            if (it != _uid_user_map.end())
            {
                _uid_user_map.erase(it);
            }
            else
            {
                DLOG_TRACE("user isn't exist, uid = " << uid);
            }
        }

        cid_t Context::getCidByUid(guid_t uid)
        {
            CSafeMutex lock(_uid_user_map_mutex);
            auto it = _uid_user_map.find(uid);
            if (it != _uid_user_map.end())
            {
                return it->second._cid;;
            }
            return nil_cid;
        }

        guid_t Context::getUidByCid(cid_t cid)
        {
            CSafeMutex lock(_uid_user_map_mutex);
            for (auto it = _uid_user_map.begin(); it != _uid_user_map.end(); it++)
            {
                if(cid >= 0 && it->second._cid == cid)
                {
                    return it->first;
                }
            }

            return nil_uid;
        }

        User *Context::getUserByUid(guid_t uid)
        {
            CSafeMutex lock(_uid_user_map_mutex);
            auto it = _uid_user_map.find(uid);
            if (it != _uid_user_map.end())
            {
                return &(it->second);
            }

            return NULL;
        }

        User *Context::getUserByCid(cid_t cid)
        {
            CSafeMutex lock(_uid_user_map_mutex);
            for (auto it = _uid_user_map.begin(); it != _uid_user_map.end(); it++)
            {
                if(cid >= 0 && it->second._cid == cid)
                {
                    return &(it->second);
                }
            }
            return NULL;
        }

        std::map<int, long> Context::getIdlerBetNum()
        {
            CSafeMutex lock(_idler_uid_map_mutex);
            std::map<int, long> map_result;
            for(auto item : _idler_uid_map)
            {
                long idler_bet_num = getIdlerBetNumByID(item.first);
                //DLOG_TRACE("idlerID: " << item.first << ", idler_bet_num: "<< idler_bet_num);
                map_result.insert(std::make_pair(item.first, idler_bet_num));
            }
            return std::move(map_result);
        }

        void Context::addIdlerCalInfo(int idlerID, CalInfo& info, int maxRound)
        {
            CSafeMutex lock(_idler_calinfo_mutex);
            auto it = _idler_calinfo.find(idlerID);
            if(it == _idler_calinfo.end())
            {
                _idler_calinfo.insert(std::make_pair(idlerID, std::vector<CalInfo> (1, info)));
            }
            else
            {
                //DLOG_TRACE("idlerID: " << idlerID << ", size: "<< it->second.size()<< ", maxRound: "<< maxRound);
                if(it->second.size() >= (unsigned int)maxRound)
                {
                    unsigned int N = it->second.size() - maxRound;
                    it->second.erase(it->second.begin(), it->second.size() > N ? it->second.begin() + N : it->second.end());
                }
                it->second.push_back(info);
                //DLOG_TRACE("idlerID: " << idlerID << ", size: "<< it->second.size()<< ", maxRound: "<< maxRound);
            }
            _round_idler_calinfo.insert(std::make_pair(idlerID, info));
        }

        void Context::addIdlerBetNum(int idlerID, long lPlayerID, std::map<long, int>& mapBetNum)
        {
            auto it = _uid_user_map.find(lPlayerID);
            if(it == _uid_user_map.end() || mapBetNum.empty())
            {
                return ;
            }
            for(auto item : mapBetNum)
            {
                for(int i= 0; i < item.second; i++)
                {
                   it->second.addIdlerBetNum(idlerID, item.first); 
                }         
            }
            
            CSafeMutex lock(_idler_uid_map_mutex);
            auto itt = _idler_uid_map.find(idlerID);
            if(itt == _idler_uid_map.end())
            {
                _idler_uid_map.insert(std::make_pair(idlerID, std::vector<long> (1, lPlayerID)));
            }
            else
            {
                auto ittt = std::find(itt->second.begin(), itt->second.end(), lPlayerID);
                if(ittt == itt->second.end())
                {
                    itt->second.push_back(lPlayerID);
                }
            }
        }

        long Context::getIdlerBetNumByID(int idlerID)
        {
            long idler_betnum = 0;
            auto it = _idler_uid_map.find(idlerID);
            if(it == _idler_uid_map.end())
            {
                return idler_betnum;
            }

            for(auto uid : it->second)
            {
                auto itt = _uid_user_map.find(uid);
                if(itt == _uid_user_map.end())
                {
                    continue;
                }
                idler_betnum += itt->second.getIdlerBetNumByID(idlerID);

                //DLOG_TRACE("idlerID: " << idlerID << ", uid: "<< uid << ", bet_num:"<< idler_betnum);
            }

            return idler_betnum;
        }

        std::map<long, int> Context::getIdlerBetNumMapByID(int iIdlerID)
        {
            CSafeMutex lock(_idler_uid_map_mutex);
            std::map<long, int> idler_betnum_map;
            auto it = _idler_uid_map.find(iIdlerID);
            if(it == _idler_uid_map.end())
            {
                return std::move(idler_betnum_map);
            }
            for(auto uid : it->second)
            {
                auto itt = _uid_user_map.find(uid);
                if(itt == _uid_user_map.end())
                {
                    continue;
                }
                for(auto item : itt->second.getIdlerBetNumMapByID(iIdlerID))
                {
                    auto itt = idler_betnum_map.find(item.first);
                    if(itt == idler_betnum_map.end())
                    {
                        idler_betnum_map.insert(std::make_pair(item.first, item.second));
                    }
                    else
                    {
                       itt->second += item.second; 
                    }
                }
            }
            return std::move(idler_betnum_map);
        } 

        void Context::setIdlerCardType(E_NN_TYPE card_type, int iIdlerID)
        {
            auto it = _idlercardstype.find(iIdlerID);
            if(it == _idlercardstype.end())
            {
                _idlercardstype.insert(std::make_pair(iIdlerID, card_type));
            }
            else
            {
                it->second = card_type;
            }
        }

        E_NN_TYPE Context::getIdlerCardType(int iIdlerID)
        {
            auto it = _idlercardstype.find(iIdlerID);
            if(it == _idlercardstype.end())
            {
                return NN_TYPE_NN_NONE;
            }
            return it->second;
        }    
    };
};
