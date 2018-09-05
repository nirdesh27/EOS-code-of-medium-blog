#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/print.hpp>
#include<string>
using namespace std;
using namespace eosio;
class hello : public eosio::contract 
{
    public:
        using contract::contract;
        // @abi table sumtable i64
        struct sumtable
        {
            account_name account;
	    uint64_t additionsum;
            uint64_t primary_key() const {return account;}
        EOSLIB_SERIALIZE(sumtable,(account)(additionsum))
        };
        typedef multi_index<N(sumtable),sumtable> _table;
        // @abi action
        void addition(account_name user,std::string memo,uint64_t delay,uint64_t a  , uint64_t b)
        {
            _table ttabs(_self,_self);
            
	        uint64_t sum = a+b;
            print(">>>>>>>>>>>>>>>>>>>>>>>");
            auto iter=ttabs.find(user);
            if(iter==ttabs.end())
            {
                print("now the sum is inserted insert_______________________\t"); 
                ttabs.emplace(_self,[&](auto& sumtable)
                {
                    sumtable.account = user;
		    sumtable.additionsum = sum;
                });
            }
            else
            {   ttabs.erase(iter);
                print(" summation added to table already_________________\t");
            }
            
        }

    // @abi action 
        void deferredtxn(account_name from,uint64_t a, uint64_t b ,string memo,uint64_t delay)
        {
            eosio::transaction txn{};
            txn.actions.emplace_back(
                eosio::permission_level(from, N(active)),
                N(testaccount),
                N(addition),
                std::make_tuple(from,memo,delay,a,b));
            txn.delay_sec = delay;
            txn.send(eosio::string_to_name(memo.c_str()), from);
            print("the deferred has been executed ____________________________________________________\n");
        }

};
EOSIO_ABI(hello,(addition)(deferredtxn))
