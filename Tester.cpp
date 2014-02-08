#include "Tester.h"
namespace mm {
    Tester::Tester(const char* _className): 
        className(_className){        
    }
    void Tester::addTestFunction(const std::string& funcName, 
                                std::function<bool()> test_fn){
        funcs.push_back(funcName);
        test_functions[funcName] = std::move(test_fn);
        results[funcName] = false;      
    }
    
    bool Tester::execTest(){
        std::for_each(funcs.begin(), funcs.end(), 
                [&](const std::string& func){
                    results[func] = test_functions[func]();
                });
    }
    
    void Tester::cleanTestResults(){
        std::for_each(funcs.begin(), funcs.end(), 
                [&](const std::string& func){
                    results[func] = false;
                });
    }
    
    bool Tester::getFinalResult() const{
        bool res = true;
        for(auto& f: funcs){
            res &= results.at(f);
        }
        return res;
    }
    
    std::string Tester::getDetailResult(){
       static const std::string FALSE("false");
       static const std::string TRUE("true");
              
       namespace bptree = boost::property_tree;
       bptree::ptree pt;
       
       pt.put("className", className);
       
       bptree::ptree func_nodes;
       for(std::string& func: funcs){
           bptree::ptree func_item;
           func_item.put(func, [&](){return results[func] ? TRUE : FALSE; }());
           func_nodes.push_back(std::make_pair("", func_item));
       }
       pt.add_child("test_func_results", func_nodes);
       pt.put("all_passed", [&](){return  getFinalResult() ? TRUE : FALSE; }());
    
       std::stringstream sstr;
       bptree:write_json(sstr, pt, false);
       return std::move(sstr.str());
    }
    
    
};