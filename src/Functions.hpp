


class FunctionBase {
   
   FUNCSIG FunctionSignature()
   virtual void Evaluate(Environment env , ParamList plist , KVar* retval)=0;
};

class ConstantFunction : public FunctionBase {
   
   FUNCSIG FunctionSignature()
   virtual void Evaluate(Environment env , ParamList plist , KVar* retval)=0;
   KVar k;
};

class VariableFunction {
   
   KVar k;
};

class UnaryFunction {
   Function arg;
public :

   virtual void Evaluate(Environment env , ParamList plist , KVar* retval)=0;
};

