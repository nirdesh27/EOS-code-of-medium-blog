# Sample_EOS_code
2.first of all you have to clone the EOS/eos from  the following link
3.https://github.com/EOSIO/eos
4.You may choose any version but i recommended any version above 1.0.7 because these have official documentation
steps are  as following
    *git clone https://github.com/eosio/eos --recursive
    *build project like this ./eosio_build.sh dawn
    *cd build  
    *make test
    *sudo make install
5.than test your nodeos like this 
   *nodeos -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console
   if nodeos run it  fine 


