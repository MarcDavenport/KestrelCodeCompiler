



#ifndef KClass_HPP
#define KClass_HPP

   
   
   

class KVarBase {
   KString type;
public :
//   KVarBase(const KString& type_name);
   KVarBase(const KString& type_name) : type(type_name) {}
   KString Type() {return type;}
};




template<class T>
class KVarType : public KVarBase {
   T t;
public :
   KVarType(const T& val);
KVarType::KVarType(const T& val) :
      KVarBase(typeid(T).name()),
      t(val) 
{}

   T& Data() {return t;}
};

class KVar {
   std::shared_ptr<KVarBase> spbase;
public :
   
};






class KClassBase {
   std::map<KString , KVar
   
   
   
};






#endif // KClass_HPP

