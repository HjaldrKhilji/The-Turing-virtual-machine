module;
#include <string>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <concepts>
#include <utility>
#include <variant>
#include <functional>
#include <cstdint>  // For uintptr_t
using std::uintptr_t;
//i used AI to track the header files needed
#include<utility>
module Printer;
import All_declarations;
import estd_regex;
namespace printing_tools {
    namespace helper_templates_for_options {
        namespace helpers_for_arithmetic_options {
            template <absolute_base::Is_String_Or_Numeric T>
            inline T read_from_string(const std::string& string_to_read_from, std::string::size_type* pos) {
                if constexpr (std::is_same_v<T, std::string>) {
                    return read_string_from_string_at_a_position(string_to_read_from, pos);
                }
                else {
                    return absolute_base::read_number_from_string_at_a_position<T>(string_to_read_from, pos);
                }
            }

            template <absolute_base::Is_String_Or_Numeric T, bool read_from_x_or_y>
            inline T read_from_string(const std::string& x, const std::string& y, std::string::size_type* x_pos, std::string::size_type* y_pos) {
                constexpr if (read_from_x_or_y) {
                    read_from_string(x, x_pos);
                }
                else {
                    read_from_string(y, y_pos);

                }
            }
            template <bool read_from_x_or_y>
            inline bool read_from_string<bool>(const std::string& x, const std::string& y, std::string::size_type* x_pos, std::string::size_type* y_pos) {
                constexpr if (read_from_x_or_y) {
                    absolute_base::convert_to_bool(x, x_pos);
                }
                else {
                    absolute_base::convert_to_bool(y, y_pos);

                }
            }
            template <bool read_from_x_or_y>
            inline char read_from_string<char>(const std::string& x, const std::string& y, std::string::size_type* x_pos, std::string::size_type* y_pos) {
                constexpr if (read_from_x_or_y) {
                    absolute_base::convert_to_char(x, x_pos);
                }
                else {
                    absolute_base::convert_to_char(y, y_pos);

                }
            }
            template <>
            inline char read_from_string<char>(const std::string& y, std::string::size_type* y_pos) {
                
                    absolute_base::convert_to_char(y, y_pos);

            }
            template <absolute_base::Numeric T>
            inline std::string convert_to_string(T source) {
                return std::to_string(source);

            }
            inline std::string convert_to_string(std::string source) {
                return source;
            }
            template <absolute_base::Numeric T>
            inline T convert_to_number(T source) {
                return source;

            }
            template <absolute_base::Numeric T>
            inline T convert_to_number(std::string source) {
                std::string::size_type position = 0;
                T result = absolute_base::read_number_from_string_at_a_position<T>(source, &position);
                if (position != source.length()) {
                    throw std::string{ "number mixed with (non numeric) charactor while taking input for an option" };
                }
                return result;

            }
            template <absolute_base::Is_String_Or_Numeric T_dest, absolute_base::Is_String_Or_Numeric T_source>
            inline T_dest convert_to_target(T_source source) {
                if constexpr (std::is_same_v<T_dest, std::string>) {
                    return convert_to_string(source);
                }
                else {
                    return convert_to_number<T_dest>(source);
                }
            }



            template <absolute_base::Is_String_Or_Numeric Internal_resperentation_type>
            struct Accumulator > {
                using Internal_resperentation = Internal_resperentation_type;
                Accumulator(Internal_resperentation arg) :internal_data{ std::move(arg) } {}

                template <absolute_base::Numeric Internal_resperentation_of_type_converted>
                Accumulator(Accumulator<Internal_resperentation_of_type_converted> arg) {
                    
                        interal_data = convert_to_target<Internal_resperentation>(arg.internal_data);
                    
                }
                void pump(std::string* string_to_pump_to, std::string::size_type* output_string_position) {
                    if constexpr (!std::is_same_v<std::string, Internal_resperentation>) {
                        std::string to_pump = std::move(internal_data);
                        *string_to_pump_to += to_pump;
                        *output_string_position += to_pump.length();
                    }
                    else {
                        std::string to_pump = std::to_string(internal_data);
                        *string_to_pump_to += to_pump;
                        *output_string_position += to_pump.length();

                    }
                }
                Internal_resperentation internal_data;
                Accumulator<Internal_resperentation> operator+(Accumulator<Internal_resperentation> y) {

                    return std::move(internal_data) + std::move(y.internal_data);// using move() due to std::strings 


                }
                Accumulator<Internal_resperentation> operator-(Accumulator<Internal_resperentation> y)
                    requires absolute_base::Numeric<Internal_resperentation> {

                    return internal_data - y.internal_data;

                }
                Accumulator<Internal_resperentation> operator*(Accumulator<Internal_resperentation> y)
                    requires absolute_base::Numeric<Internal_resperentation> {

                    return internal_data * y.internal_data;

                }
                Accumulator<Internal_resperentation> operator/(Accumulator<Internal_resperentation> y)
                    requires absolute_base::Numeric<Internal_resperentation> {

                    return internal_data / y.internal_data;

                }
            };


            inline bool is_char_digit(const char c) {

                if (c >= '0' && c <= '9') {
                    return true;
                }
                else {
                    return false;
                }
            }
            enum class Type_tag: unsigned char{uintptr_tag=1, long_double_tag=2, string_tag=3,
            type_in_vector_tag=4, type_in_map_tag=5, type_in_hash_map_tag=6, nested_type=7, heterogeneous_array=8, extended_types=9};
            struct Extented_type_info{
            Type_tag tag;
            union{
            uintptr_t index;//for Extented_types 
            uintptr_t  size;//for hetrogenous_array_type
            }
            };       
            
            std::vector<std::vector<Extented_type_info>> vector_containing_types;
            std::map<uintptr_t,std::vector<Extented_type_info>> map_containing_types;
            std::unordered_map<uintptr_t,std::vector<Extented_type_info>> 
            unordered_map_containing_types;
            //ALL_ActiO0n0OnOps_for_simple0OPS is ALL action on ops for simple ops, the name is bad on purpose (to avoid name conflcts and to stick out as something wierd so the mantainer(still probably me in the future), knows it can have bugs
            //by simple ops, i mean, you cant branch, unless lhs(or rhs) does it for you
            #define ALL_ActiO0n0OnOps_for_simple0OPS(lhs, rhs, op, name_of_the_class_used)\
                        if constexpr(op_action_type==_true) {\
                            op(lhs,second_arg);\
                        }\
                        else{\
                            if constexpr (op_action_type==_nuteral) {\
                                return op(lhs,second_arg);\
                            }\
                            else{\
                                return name_of_the_class_used<type_name>{op(lhs, second_arg)};\
                            }\
                        }
            // _true means assigment operators, _nuteral means compairision/ordering operators, _false/other means binary operators (eg + - * /,etc) that return a by value result 
             #define Repitative_CAase_F0or_nested_the_NaMe_is_FUnny_on_PURPOSE(lhs,rhs, op, Type_tag, name_of_the_class_used_in)\
                            case Type_tag::nested_type:\
                                auto& raw_pair= *(static_cast<std::pair<Extented_type_info, name_of_the_class_used_in>*>(rhs));\
                                auto size= (raw_pair->first).size;\
                                char *raw_mem = static_cast<char*>((raw_pair.second).ptr);\
                                name_of_the_class_used_in* array= reinterpret_cast<name_of_the_class_used_in*>(raw_mem+sizeof(Extented_type_info));\
                                if constexpr(op_action_type==_true) {\
                                    for(uintptr_t i=0; i<size; i++){\
                                        op(lhs.second, array[i]);\
                                    }\
                                }\
                                else{\
                                    if constexpr (op_action_type==_nuteral) {\
                                    for(uintptr_t i=0; i<size; i++){\
                                        if(!op(lhs.second, array[i])){\
                                            return false;\
                                        }\
                                    }\
                                    return true;\
                                    }\
                                    else{\
                                    auto lhs_temp= lhs.second;\
                                    for(uintptr_t i=0; i<size; i++){\
                                    op(lhs_temp, array[i]);\
                                    }\
                                    return name_of_the_class_used_in{Type_tag, lhs_temp};\
                                    }\
                                    }\
                                break;\
                                        }
   



            template <typename tag_of_type_to_construct_from, typename class_used_in>
            inline construct_void_pointer(void **ptr, tag_of_type_to_construct_from obj ){
                if constexpr(std::is_same_v(tag_of_type_to_construct_from, uintptr_t) {
                        *ptr= static_cast<void*>(new std::pair<Type_tag, uintptr>{Type_tag::uintptr_tag,obj});  
                }
                else if(std::is_same_v(tag_of_type_to_construct_from, long double){
                        *ptr= static_cast<void*>(new std::pair<Type_tag, long double>{Type_tag::long_double_tag,obj});  
                }
                else if(std::is_same_v(tag_of_type_to_construct_from, std::string){
                        *ptr= static_cast<void*>(new std::pair<Type_tag,  std::string>{ Type_tag::string_tag,obj});  
                }
                else if(std::is_same_v(tag_of_type_to_construct_from, class_used_in){
                    Extented_type_info& temp =*(static_cast<Extented_type_info*>(obj.ptr));
                    const class_used_in& source_array= *(static_cast<class_used_in*>(static_cast<char*>(obj.ptr)+sizeof(Extented_type_info)));
                    uintptr_t size= temp.size;
                    uintptr_t array_size_in_bytes= sizeof(Extended_types*)*size; 
                    uintptr_t element_size_in_bytes=sizeof(Extended_types)*size;
                    char *raw_mem= new char[array_size_in_bytes+element_size_in_bytes+sizeof(Extented_type_info)];
                    new (reinterpret_cast<Extented_type_info*>) Extented_type_info{Type_tag::heterogeneous_array, size};
                    class_used_in* array= reinterpret_cast<class_used_in*>(raw_mem+sizeof(Extented_type_info));
                    class_used_in* end= array+array_size_in_bytes;
                    for(int i=0; i<vector_containing_nested_type_info.length(); i++){
                        array[i]=end+(i*element_size_in_bytes); 
                            new (array[i]) class_used_in{source_array[i]};
                        }
                    *ptr= static_cast<void*>(raw_mem);  
                }
               
                
            }




            template <typename Op_two_type, typename op, ternary_state op_action_type, typename name_of_the_class_used_in>
            requires std::is_arithmetic_v<Op_two_type> || std::is_same_v<std:string, Op_two_type>
            inline std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Hetrogenous_array_type>>
            void_operator_generator(void **ptr, Op_two_type second_arg) {  //the manliest op gen ever, made by a real man (THE 6'3 KING (me, ofcourse))     
            switch(static_cast<Type_tag*>(*ptr)){
                case Type_tag::uintptr_tag:
                if constexpr (!std::is_same_v<uintptr_t, Op_two_type>)   {
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(static_cast<std::pair<Type_tag, uintptr_t>*>(*ptr)->second), second_arg, op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<long double, Op_two_type>)  {
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(static_cast<std::pair<Type_tag, uintptr_t>*>(*ptr)->second), uintptr_t{second_arg},op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<std::string, Op_two_type>)  {
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(static_cast<std::pair<Type_tag, uintptr_t>*>(*ptr)->second),  convert_to_number<uintptr_t>(second_arg),op, name_of_the_class_used_in)
                }
                    break;
                case Type_tag::long_double_tag:
                if constexpr (!std::is_same_v<uintptr_t, Op_two_type>)  {
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(static_cast<std::pair<Type_tag, long double>*>(*ptr)->second),  long double{second_arg}, op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<long double, Op_two_type>)  {
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(static_cast<std::pair<Type_tag, long double>*>(*ptr)->second), second_arg,op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<std::string, Op_two_type>)  {
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(static_cast<std::pair<Type_tag, long double>*>(*ptr)->second),  convert_to_number<long double>(second_arg),op, name_of_the_class_used_in)
                }
                    break;
                case Type_tag::string_tag:
                if constexpr (!std::is_same_v<uintptr_t, Op_two_type>)  {
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(static_cast<std::pair<Type_tag, std::string>*>(*ptr)->second),  std::to_string(second_arg),op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<long double, Op_two_type>)  {
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(static_cast<std::pair<Type_tag, std::string>*>(*ptr)->second), std::to_string(second_arg),op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<std::string, Op_two_type>)  {
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(static_cast<std::pair<Type_tag, std::string>*>(*ptr)->second),  second_arg,op, name_of_the_class_used_in)
                }
                break;
            }
            }




            template<typename op, ternary_state op_action_type, typename name_of_the_class_used_in>
            std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Hetrogenous_array_type>> 
            void_op_generator(void **ptr, void* second_arg) {       
            
            switch(static_cast<Type_tag*>(*ptr)){
                case Type_tag::uintptr_tag:
                    auto& lhs = *(static_cast<std::pair<Type_tag, uintptr>*>(*ptr));
                    switch((static_cast<std::pair<Type_tag, uintptr>*>(second_arg)->first){
                        case Type_tag::uintptr_tag:
                            ALL_ActiO0n0OnOps_for_simple0OPS(*(lhs->second), static_cast<std::pair<Type_tag, uintptr>*>(second_arg)->second,op,name_of_the_class_used_in);
                            break;
                        case Type_tag::long_double_tag:
                            ALL_ActiO0n0OnOps_for_simple0OPS(*(lhs->second), uintptr{static_cast<std::pair<Type_tag, long double>*>(second_arg)->second},op, name_of_the_class_used_in);
                            break;
                        case Type_tag::string_tag:
                            ALL_ActiO0n0OnOps_for_simple0OPS(*(lhs->second), convert_to_number<uintptr>(std::static_cast<std::pair<Type_tag, std::string>*>(second_arg)->second,op,name_of_the_class_used_in);
                            break;
                        REPETETIVE_CASE_STATEMENT_OPS_ON_EXTENDED_AND_HETROGENOUS0Types_f0r_Hetrogenous_ARRAYS_FUNNY_NAME_ON_PURPOSE(lhs, second_arg,  op,Type_tag::uintptr_tag, name_of_the_class_used_in)
                    }
                case Type_tag::long_double_tag:
                    auto* lhs = static_cast<std::pair<Type_tag, long double>*>(*ptr);
                    switch((static_cast<std::pair<Type_tag, uintptr>*>(second_arg)->first){
                        case Type_tag::uintptr_tag:
                            ALL_ActiO0n0OnOps_for_simple0OPS(*(lhs->second),long double{static_cast<std::pair<Type_tag, uintptr>*>(second_arg)->second},op, name_of_the_class_used_in)
                            break;
                        case Type_tag::long_double_tag:
                        ALL_ActiO0n0OnOps_for_simple0OPS(*(lhs->second),static_cast<std::pair<Type_tag, long double>*>(second_arg)->second,op, name_of_the_class_used_in)
                        break;
                        case Type_tag::string_tag:
                        ALL_ActiO0n0OnOps_for_simple0OPS(*(lhs->second),convert_to_number<long double>(std::static_cast<std::pair<Type_tag, std::string>*>(second_arg.ptr)->second),op, name_of_the_class_used_in)
                        break;
                        REPETETIVE_OPS_ON_EXTENDED_AND_HETROGENOUS0Types_f0r_Hetrogenous_ARRAYS_FUNNY_NAME_ON_PURPOSE(lhs, second_arg, op, Type_tag::long_double_tag, name_of_the_class_used_in);
                        }
                    break;
                case Type_tag::string_tag:
                    auto* lhs = static_cast<std::pair<Type_tag, std::string>*>(*ptr);
                    switch((static_cast<std::pair<Type_tag, uintptr>*>(second_arg)->first){
                    case Type_tag::uintptr_tag:
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(lhs->second), std::to_string(static_cast<std::pair<Type_tag, uintptr>*>(second_arg)->second),op, name_of_the_class_used_in)
                    break;
                    case Type_tag::long_double_tag:
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(lhs->second), std::to_string(static_cast<std::pair<Type_tag, long double>*>(second_arg)->second),op, name_of_the_class_used_in)
                    break;
                    case Type_tag::string_tag:
                    ALL_ActiO0n0OnOps_for_simple0OPS(*(lhs->second), static_cast<std::pair<Type_tag, std::string>*>(second_arg)->second,op,name_of_the_class_used_in)
                    break;
                    REPETETIVE_OPS_ON_EXTENDED_AND_HETROGENOUS0Types_f0r_Hetrogenous_ARRAYS_FUNNY_NAME_ON_PURPOSE(lhs, second_arg, op,Type_tag::string_tag, name_of_the_class_used_in);
                case Type_tag::nested_type:
                        Extented_type_info& temp_info =*(static_cast<Extented_type_info*>(*ptr));
                        Extented_type_info& temp_info_source =*(static_cast<Extented_type_info*>(second_arg));
                        if(temp_info.size == temp_info_source.size){
                        throw std::string{"size mismatch for two hetrogenous arrays operands"};
                        } 
                        uintptr_t size= temp_info.size;
                        uintptr_t array_size_in_bytes= sizeof(name_of_the_class_used_in*)*size; 
                        uintptr_t element_size_in_bytes=sizeof(name_of_the_class_used_in)*size;
                        name_of_the_class_used_in* array= reinterpret_cast<name_of_the_class_used_in*>(static_cast<char*>(ptr)+sizeof(Extented_type_info));
                        name_of_the_class_used_in* source_array= reinterpret_cast<name_of_the_class_used_in*>(static_cast<char*>(second_arg)+sizeof(Extented_type_info));
                        if constexpr(op_action_type==_true) {
                            for(uintptr_t i=0; i<size; i++){
                                op(source_array[i], array[i]);
                                }
                            }
                            else{
                                if constexpr (op_action_type==_nuteral) {
                                    for(uintptr_t i=0; i<size; i++){
                                        if(!op(source_array[i], array[i])){
                                            return false;
                                        }
                                    }
                                    return true;
                                    }
                                else{
                                    auto lhs_temp= lhs.second;
                                    for(uintptr_t i=0; i<size; i++){
                                    op(source_array[i], array[i]);
                                    }
                                    return name_of_the_class_used_in{Type_tag, lhs_temp};
                                    }
                    }
                
                default:

            }
            }
            struct Polymoprhic_extensible_engine{
            void *ptr;
            template <Type_tag tag_of_type_to_construct_from>
            inline Polymoprhic_extensible_engine(tag_of_type_to_construct_from obj)
            {
              construct_void_pointer<Polymoprhic_extensible_engine>(&ptr, obj);
            }
            template <typename op, typename op, ternary_state op_action_type>
            requires std::is_arithmetic_v<Op_two_type> || std::is_same_v<std:string, Op_two_type>
            inline std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Polymoprhic_extensible_engine>>
            void_operator_generator(Op_two_type second_arg) {
                void_operator_generator<Op_two_type, op, op_action_type, Polymoprhic_extensible_engine>, op_action_type(&ptr,second_arg);
            }
                    
            template<typename op, ternary_state op_action_type>
            inline std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Polymoprhic_extensible_engine>> 
            void_op_generator(Polymoprhic_extensible_engine second_arg){
                void_op_generator<op, op_action_type, Polymoprhic_extensible_engine>(&ptr, second_arg.ptr);
            }
            ~Polymoprhic_extensible_engine(){
            switch(static_cast<Type_tag*>(ptr).tag){
                case Type_tag::uintptr_tag:
                    delete static_cast<std::pair<Extented_type_info, uintptr_t>*>(ptr);
                    return;
                case Type_tag::long_double_tag:
                    delete static_cast<std::pair<Extented_type_info, long double>*>(ptr);
                    return;
                case Type_tag::string_tag:
                    delete static_cast<std::pair<Extented_type_info, std::string>*>(ptr);
                    return;
                default:
            }

            Extented_types* array= static_cast<Extented_types*>(ptr+sizeof(Extented_type_info));
            for(int i=0; i<vector_containing_nested_type_info.length(); i++){
                ~array[i];
            }
            delete[] reinterpret_cast<char*>(ptr);
            }
            };
            struct Extented_types:public Polymoprhic_extensible_engine{
//I know its not recommneded to provide "just in case aliases,but this is to show what is getting allocated in each case:
            using Nested_type= std::pair<Extented_type_info, Polymoprhic_extensible_engine*>;
            using Ordinary_type_int= std::pair<Type_tag, uintptr_t>;
            using Ordinary_type_double= std::pair<Type_tag, long double>;
            using Ordinary_type_string= std::pair<Type_tag, std::string>;
            using Ordinary_type_hetrogenous_array= std::pair<Type_tag, Hetrogenous_array>;
            using Hetrogenous_array= std::pair<Type_tag, Hetrogenous_array>;
         
             void* ptr;
            Extented_types(const Extented_type_info& info, const std::string& string_to_read_from, 
                std::string:size_type* pos )
            {
                switch(info.tag){
                    case Type_tag::uintptr_tag:
                    ptr= static_cast<void*>(new std::pair<Type_tag, uintptr_t>
                    {Type_tag::uintptr_tag,read_from_string<uintptr_t>(string_to_read_from, pos)});
                    return;
                    case Type_tag::long_double_tag:
                    ptr= static_cast<void*>(new std::pair<Type_tag, long double>
                    {Type_tag::long_double_tag,read_from_string<long double>(string_to_read_from, pos)});
                    return;
                    case Type_tag::string_tag:
                    ptr= static_cast<void*>(new std::pair<Type_tag, std::string>
                    {Type_tag::string_tag,read_from_string<std::string>(string_to_read_from, pos)});
                    return;
                    case Type_tag::heterogeneous_array:
                    Type_tag nested_tag= static_cast<Type_tag>(read_from_string<unsigned char>(string_to_read_from, pos));
                    ptr= static_cast<void*>(new std::pair<Type_tag, Hetrogenous_array>
                    {Type_tag::heterogeneous_array,{nested_tag, source, pos});
                    return;
                    default:
                }
                vector<Extented_type_info>* extra_info_for_extented_types;
                switch(info.tag){
                    case Type_tag::vector_containing_types:
                    extra_info_for_extented_types= vector_containing_types[info.index];
                    case Type_tag::type_in_map_tag:
                    extra_info_for_extented_types= map_containing_types[info.index];
                    case Type_tag::type_in_hash_map_tag:
                    extra_info_for_extented_types= unordered_map_containing_types[info.index];
                    default:
                    
                }
                    auto vec_size= vector_containing_nested_type_info.length();
                    uintptr_t array_size_in_bytes= sizeof(Extented_types*)*vec_size; 
                    uintptr_t element_size_in_bytes=sizeof(Extented_types)*vec_size;
                    char *raw_mem= new char[array_size_in_bytes+element_size_in_bytes+sizeof(Extented_type_info)];
                    new (reinterpret_cast<Extented_type_info*>) Extented_type_info{info};
                    Polymoprhic_extensible_engine* array= reinterpret_cast<Polymoprhic_extensible_engine*>(raw_mem+sizeof(Extented_type_info));
                    Polymoprhic_extensible_engine* end= array+array_size_in_bytes;
                    for(int i=0; i<vec_size; i++){
                        array[i]=end+(i*element_size_in_bytes); 
                        new (array[i]) Extented_types{vector_containing_nested_type_info[i], source, location} };
                    }
                    ptr= static_cast<void*>(raw_mem);
                  
            }

    
            };
            struct Hetrogenous_array_type{
//I know its not recommneded to provide "just in case aliases,but this is to show what is getting allocated in each case:
            using Nested_type= std::pair<Extented_type_info, hetrogenous_array_type*>;
            using Ordinary_type_int= std::pair<Type_tag, uintptr_t>;
            using Ordinary_type_double= std::pair<Type_tag, long double>;
            using Ordinary_type_string= std::pair<Type_tag, std::string>;
            using Element_of_extended_types= std::pair<Type_tag, Extented_types<Hetrogenous_array_type>>;
            using Extented_types= Extented_types<Hetrogenous_array_type>;//for avoiding wierd template specialization syntax

             void* ptr;
            Hetrogenous_array_type(Type_tag info, const std::string& string_to_read_from, 
                std::string:size_type* pos )
            {
                switch(info){
                    case Type_tag::uintptr_tag:
                    ptr= static_cast<void*>(new std::pair<Type_tag, uintptr>{Type_tag::uintptr_tag,read_from_string<uintptr>(string_to_read_from, pos)});  
                    return;
                    case Type_tag::long_double_tag:
                    ptr= static_cast<void*>(new std::pair<Type_tag, long double>{Type_tag::long_double_tag,read_from_string<long double>(string_to_read_from, pos)});  
                    return;
                    case Type_tag::string_tag:
                    ptr= static_cast<void*>(new std::pair<Type_tag, std::string>{Type_tag::string_tag,read_from_string<std::string>(string_to_read_from, pos)});  
                    return;
                    case Type_tag::extented_types:
                    ptr= static_cast<void*>(new std::pair<Type_tag, Extented_types>{Type_tag::extented_types,read_from_string<Extented_types>(string_to_read_from, pos)});  
                    return;
                    default:
                }
                    uintptr_t size= read_from_string<uintptr_t>(string_to_read_from, pos);
                    uintptr_t array_size_in_bytes= sizeof(Hetrogenous_array_type*)*size; 
                    uintptr_t element_size_in_bytes=sizeof(Hetrogenous_array_type)*size;
                    char *raw_mem= new char[array_size_in_bytes+element_size_in_bytes+sizeof(Extented_type_info)];
                    new (reinterpret_cast<Extented_type_info*>) Extented_type_info{Type_tag::heterogeneous_array, size};
                    Hetrogenous_array_type* array= reinterpret_cast<Hetrogenous_array_type*>(raw_mem+sizeof(Extented_type_info));
                    Hetrogenous_array_type* end= array+array_size_in_bytes;
                    for(int i=0; i<size; i++){
                        array[i]=end+(i*element_size_in_bytes); 
                        new (array[i]) Hetrogenous_array_type{static_cast<Type_tag>(read_from_string<unsigned char>(string_to_read_from, pos)),source, location };
                    }
                    ptr= static_cast<void*>(raw_mem);
                    
                
                  
            }
            template <Type_tag tag_of_type_to_construct_from>
            inline Hetrogenous_array_type(tag_of_type_to_construct_from obj)
            {
              construct_void_pointer<Hetrogenous_array_type>(&ptr, obj);
            }
            template <typename , typename op, ternary_state op_action_type>
            requires std::is_arithmetic_v<Op_two_type> || std::is_same_v<std:string, Op_two_type>
            inline std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Hetrogenous_array_type>>
            void_operator_generator(Op_two_type second_arg) {
            void_operator_generator<Op_two_type, op, op_action_type,Hetrogenous_array_type> op_action_type(&ptr,second_arg);
            }
                    
            template<typename op, ternary_state op_action_type>
            inline std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Hetrogenous_array_type>> 
            void_op_generator(Hetrogenous_array_type second_arg){
                void_op_generator<op, op_action_type, Hetrogenous_array_type>(&ptr, second_arg.ptr);
            }

            template<typename op, ternary_state op_action_type>
            inline std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Hetrogenous_array_type>> 
            void_op_generator(Extended_types second_arg){
                void_op_generator<op, op_action_type, Hetrogenous_array_type>(&ptr, second_arg.ptr);
            }
            ~Hetrogenous_array_type(){
            switch(static_cast<Type_tag*>(ptr)){
                case Type_tag::uintptr_tag:
                    delete static_cast<std::pair<Type_tag, uintptr_t>*>(ptr);
                    break;
                case Type_tag::long_double_tag:
                    delete static_cast<std::pair<Type_tag, long double>*>(ptr);
                    break;
                case Type_tag::string_tag:
                    delete static_cast<std::pair<Type_tag, std::string>*>(ptr);
                    break;
                case Type_tag::extented_types:
                    delete static_cast<std::pair<Type_tag, Extented_types>*>(ptr);
                    break;
            }
                uintptr_t size= static_cast<std::pair<Extented_type_info, void>*>(ptr)->size;
                 Hetrogenous_array_type* array= static_cast<Hetrogenous_array_type*>(static_cast<char*>(obj.ptr)+sizeof(Extented_type_info));
                for(int i=0; i<size; i++){
                ~array[i];
                }
                 delete[] reinterpret_cast<char*>(ptr);
                    }
            };
            //the polymorphic types are polymorphic in the sense that the size is the same, so its not a technical name
            struct fixed_size_strings{
            std::string* ptr;
            fixed_size_strings(std::string string_to_build_it_with): 
            ptr{    new std::string{  std::move( string_to_build_it_with )  }    } {}
            
            ~fixed_size_strings(){
                delete ptr;
            }

            };
            inline std::string&& get(std::string&& a){
                return std::move(a);
            }            
            inline std::string& get(std::string& a){
                return a;
            }
            inline std::string&& get(fixed_size_strings&& a){
                return std::move(*(a.ptr));
            }            
            inline std::string& get(fixed_size_strings& a){
                return *(a.ptr);
            }
            
            struct fixed_size_floats{
            long double *ptr;
            fixed_size_floats(long double double_to_build_it_with): 
            ptr{   new long double   } {}

            ~fixed_size_floats(){
                delete ptr;
            }

            };
            template<typename Op_type>
                bool all_comparision_imp_generator(Hetrogenous_array_type& lhs, const Polymorphic_accumulator& rhs, Op_type operator_name) {
                }
            struct Polymorphic_accumulator {
                constexpr common_size= sizeof(uintptr_t);
                using long_double= std::conditional<sizeof(long double)<common_size, long double,
                    std::conditional<sizeof(double)<common_size, double, 
                    std::conditional<sizeof(float)>common_size, float, 
                    fixed_size_floats>
                    >
                    >
                using fixed_size_strings_t== std::conditional<sizeof(std::string)<common_size, std::string>;
                using Hetrogenous_array_type=Hetrogenous_array_type;
                using Extented_types= Extented_types<Hetrogenous_array_type>;
                union{
                    uintptr_t unsigned_num;
                    intptr_t signed_num;
                    long_double floating_point;
                    fixed_size_strings_t strings;
                    Hetrogenous_array_type diverse_array;
                    Extented_types Extended_types;   
                }
                Type_tag True_type;

                void pump(std::string* string_to_pump_to, std::string::size_type* output_string_position) {
                    std::visit([&](auto&& arg) {
                        if constexpr (!std::is_same_v<fixed_size_strings, decltype(arg)>) {
                            const std::string& string_to_pump=  arg.get();
                            *string_to_pump_to += string_to_pump;
                            *output_string_position+=string_to_pump.length();
                            }
                        else {
                            std::string stringified_num=std::to_string(arg);
                           *string_to_pump_to += stringified_num;
                           *output_string_position += stringified_num.length();

                        }
                        
                        }, internal_data);
                }
                void pump_move(std::string* string_to_pump_to, std::string::size_type* output_string_position) {
                    std::visit([&](auto&& arg) {
                        
                      if constexpr (!std::is_same_v<fixed_size_strings, decltype(arg)>) {
                            const std::string string_to_pump=  arg.get_moved();
                            *string_to_pump_to += string_to_pump;
                            *output_string_position+=string_to_pump.length();
                            }
                        else {
                            std::string stringified_num=std::to_string(arg);
                           *string_to_pump_to += stringified_num;
                           *output_string_position += stringified_num.length();

                        }
                        }, internal_data);
                }
                void pump_polymorphic_copy_semantics(std::string* string_to_pump_to, std::string::size_type* output_string_position) {
                    std::visit([&](auto&& arg) {
                        if constexpr (!std::is_same_v<fixed_size_strings, decltype(arg)>) {
                            bool copy_or_move=read_from_string<bool>(string_to_pump_to, output_string_position);
                            if(copy_or_move){
                            const std::string& string_to_pump=  arg.get();
                            *string_to_pump_to += string_to_pump;
                            *output_string_position+=string_to_pump.length();
                            }
                            else{
                            const std::string string_to_pump=  arg.get_moved();
                            *string_to_pump_to += string_to_pump;
                            *output_string_position+=string_to_pump.length();   
                            }
                            
                            
                        }
                        else {
                            std::string stringified_num=std::to_string(arg);
                           *string_to_pump_to += stringified_num;
                           *output_string_position += stringified_num.length();  

                        }
                        
                        }, internal_data);
                }

                template<typename Op_type>
                bool all_comparision_imp_generator( Polymorphic_accumulator& lhs,  Polymorphic_accumulator& rhs, Op_type operator_name) {
                    Polymorphic_accumulator result = std::visit([&](auto&& a, auto&& b) -> Polymorphic_accumulator {
                    if constexpr (std::is_same_v<fixed_size_strings, decltype(a)>) {
                        if constexpr (std::is_same_v<fixed_size_strings, decltype(b)>) {
                            return operator_name(a.get(), b.get());

                        }
                        else {
                            return operator_name(a.get(), std::to_string{ b });

                        }
                    }
                    else {
                        if constexpr (std::is_same_v<fixed_size_strings, decltype(b)>) {
                            try {
                                if constexpr (std::is_same_v<uintptr_t, decltype(a)>) {
                                    return operator_name(a, convert_to_number<uintptr_t>(b.get()));
                                }
                                else if constexpr (std::is_same_v<long double, decltype(a)>) {
                                    return operator_name(b, convert_to_number<long double>(b.get()));

                                }
                            }
                                catch (std::string& error_from_converter) {
                                    throw std::string{ "DYNAMIC ARETHIMETIC ENGINE: "+ error_from_converter+'.'};
                                }
                            
                        }
                        else {
                            return operator_name(a, b);

                        }
                    }
                }, lhs, rhs);
                return result;
                }
                inline bool operator==(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_comparision_imp_generator(*this, polymorphic_accumulator, std::equal_to <>{});

                }
                inline bool operator!=(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_comparision_imp_generator(*this, polymorphic_accumulator, std::not_equal_to <>{});

                }
                inline bool operator<(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_comparision_imp_generator(*this, polymorphic_accumulator, std::less <>{});

                }
                inline bool operator>(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_comparision_imp_generator(*this, polymorphic_accumulator, std::greater <>{});

                }
                inline bool operator<=(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_comparision_imp_generator(*this, polymorphic_accumulator, std::less_equal <>{});

                }
                inline bool operator>=(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_comparision_imp_generator(*this, polymorphic_accumulator, std::greater_equal <>{});

                }
                inline Polymorphic_accumulator operator+(Polymorphic_accumulator polymorphic_accumulator) {
                    Polymorphic_accumulator result = std::visit([&](auto&& a, auto&& b) -> Polymorphic_accumulator {

                        if constexpr (std::is_same_v<fixed_size_strings, decltype(a)>) {
                            if constexpr (!std::is_same_v<fixed_size_strings, decltype(b)>) {
                                return Polymorphic_accumulator{ a.get() + b.get() };//used std::move() because of strings

                            }
                            else {
                                return Polymorphic_accumulator{ a.get() + std::to_string(b) };//used std::move() because of strings

                            }
                        }
                        else {
                        if constexpr (std::is_same_v<fixed_size_strings, decltype(b)>) {
                        return Polymorphic_accumulator{ std::to_string(a) + b.get() };//used std::move() because of strings
                        }
                        else {
                        return Polymorphic_accumulator{ a.get()+b.get() };
                        }
                        }
                        }, *this, polymorphic_accumulator);
                    return result;

                }
                inline Polymorphic_accumulator plus_with_move(Polymorphic_accumulator polymorphic_accumulator) {
                    Polymorphic_accumulator result = std::visit([&](auto&& a, auto&& b) -> Polymorphic_accumulator {

                        if constexpr (std::is_same_v<std::string, decltype(a)>) {
                            if constexpr (!std::is_same_v<std::string, decltype(b)>) {
                                return Polymorphic_accumulator{ std::move(a) + std::move(b) };//used std::move() because of strings

                            }
                            else {
                                return Polymorphic_accumulator{ std::move(a) + std::to_string(b) };//used std::move() because of strings

                            }
                        }
                        else {
                        if constexpr (std::is_same_v<std::string, decltype(b)>) {
                        return Polymorphic_accumulator{ std::to_string(a) + std::move(b) };//used std::move() because of strings

                            }
                            else {
                                return Polymorphic_accumulator{ a+b };

                            }
                        }
                        }, *this, polymorphic_accumulator);
                    return result;

                }

                template<typename Op_type>
                inline Polymorphic_accumulator all_operator_impl_generator(const Polymorphic_accumulator& lhs, const Polymorphic_accumulator& rhs, Op_type operator_name) {
                    
                    Polymorphic_accumulator result = std::visit([&](auto&& a, auto&& b) -> Polymorphic_accumulator {
                        //I used && to enable the good old reference forwading
                        if constexpr (requires { operator_name(a, b); }) {
                           
                           return Polymorphic_accumulator{ operator_name(a, b) };
                            
                        }
                        

                            else {
                            throw std::string{ "DYNAMIC ARETHIMETIC ENGINE std::visit all_opoerator_impl compile time error, first paremeter is std::string, type mismatch. ") };
                        }}
                            , lhs.internal_data, rhs.internal_data);
                        return result;
                    
                    
                   }
                
                inline Polymorphic_accumulator operator-(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_operator_impl_generator(*this, polymorphic_accumulator, std::minus<>{});

                }
                inline Polymorphic_accumulator operator*(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_operator_impl_generator(*this, polymorphic_accumulator, std::multiplies<>{});

                }
                inline Polymorphic_accumulator operator*(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_operator_impl_generator(*this, polymorphic_accumulator, std::divides<>{});

                }
                inline Polymorphic_accumulator operator|(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_operator_impl_generator(*this, polymorphic_accumulator, std::bit_or<>{});

                }
                inline Polymorphic_accumulator operator&(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_operator_impl_generator(*this, polymorphic_accumulator, std::bit_and<>{});

                }
                inline Polymorphic_accumulator operator^(Polymorphic_accumulator polymorphic_accumulator) {
                    return all_operator_impl_generator(*this, polymorphic_accumulator, std::bit_xor<>{});

                }

            };
            Polymorphic_accumulator read_polymorphically_from_string(const std::string& string_to_read_from, std::string::size_type* pos) {
              
                    if (is_char_digit(string_to_read_from[*pos])) 
                        {
                            return Polymorphic_accumulator{ read_from_string<uintptr_t>(string_to_read_from, pos) };

                         }
                    else if (string_to_read_from[*pos] == '.') {
                        return Polymorphic_accumulator{ read_from_string<long double>(string_to_read_from, pos) };
                    }
                    


                    else {
                        return  Polymorphic_accumulator{ string_index{read_from_string<std::string>(string_to_read_from, pos)} };
                    }
                    
                

                

            }
            template <bool read_from_x_or_y>
            inline Polymorphic_accumulator read_polymorphically_from_string(const std::string& x, const std::string& y, std::string::size_type* x_pos, std::string::size_type* y_pos) {
                constexpr if (read_from_x_or_y) {
                    read_polymorphically_from_string(x, x_pos);
                }
                else {
                    read_polymorphically_from_string(y, y_pos);

                }
            }
        }
    }
}


















































