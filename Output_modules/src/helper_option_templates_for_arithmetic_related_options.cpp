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
#include<atomic>
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
            constexpr common_size= sizeof(uintptr_t);
                using long_double= std::conditional<sizeof(long double)<common_size, long double,
                    std::conditional<sizeof(double)<common_size, double, 
                    std::conditional<sizeof(float)>common_size, float, 
                    fixed_size_floats>
                    >
                    >
                using fixed_size_strings_t== std::conditional<sizeof(std::string)<common_size, std::string>;
                using Hetrogenous_array_type=Hetrogenous_array_type;
 
            enum class Type_tag : unsigned char {
                    intptr_tag = 0,
                    uintptr_tag = 1, 
                    long_double_tag = 2,
                    string_tag = 3,
                    vector_intptr = 4,
                    vector_uintptr = 5,
                    vector_double = 6,
                    vector_string = 7,
                    nested_type = 8,
                    heterogeneous_array = 9,
                    extended_types = 10,
                    atomic_nested_owning_type = 11,
                    semaphore = 12,
                    command_line_executioner = 13,
                    socket_executioner = 14,
                    jthread_nested_machine = 15,
                    type_in_vector_tag = 16,
                    type_in_map_tag = 17,
                    type_in_hash_map_tag = 18,
                    
                };
               enum class Type_tag_for_input : unsigned char {//has extra type tags that translate into nested_type, the type tags are:
                    //heterogeneous_array,extended_types, type_in_vector_tag, type_in_map_tag, type_in_hash_map_tag
                    intptr_tag = 0,
                    uintptr_tag = 1,
                    long_double_tag = 2,
                    string_tag = 3,
                    vector_intptr = 4,
                    vector_uintptr = 5,
                    vector_double = 6,
                    vector_string = 7,
                    nested_type = 8,
                    heterogeneous_array = 9,
                    extended_types = 10,
                    atomic_nested_owning_type = 11,
                    semaphore = 12,
                    command_line_executioner = 13,
                    socket_executioner = 14,
                    jthread_nested_machine = 15,
                    type_in_vector_tag = 16,
                    type_in_map_tag = 17,
                    type_in_hash_map_tag = 18,
                    
                };
            constexpr inline unsigned char produce_jump_index(Type_tag type_x, Type_tag type_y){
                (static_cast<unsigned char>(type)>>4)+type_y;
            }
            
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
             template<typename Op, ternary_state op_action_type, typename Name_of_the_class_used_in, typename Lhs_t, typename Rhs_t>
            inline  std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Hetrogenous_array_type>> 
            all_action_on_ops_for_simple_ops(Lhs_t lhs,Rhs_t rhs){
                        if constexpr(op_action_type==_true) {
                            Op(lhs,rhs);
                        }
                        else{
                            if constexpr (op_action_type==_nuteral) {
                                return Op(lhs,rhs);
                            }
                            else{
                                return Name_of_the_class_used_in<type_name>{Op(lhs, rhs)};
                            }
                        }
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
                    uintptr_t array_size_in_bytes= sizeof(class_used_in*)*size; 
                    uintptr_t element_size_in_bytes=sizeof(class_used_in)*size;
                    char *raw_mem= new char[array_size_in_bytes+element_size_in_bytes+sizeof(Extented_type_info)];
                    new (reinterpret_cast<Extented_type_info*>) Extented_type_info{Type_tag::nested_type, size};
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
                    all_action_on_ops_for_simple_ops(*(static_cast<std::pair<Type_tag, uintptr_t>*>(*ptr)->second), second_arg, op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<long double, Op_two_type>)  {
                    all_action_on_ops_for_simple_ops(*(static_cast<std::pair<Type_tag, uintptr_t>*>(*ptr)->second), uintptr_t{second_arg},op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<std::string, Op_two_type>)  {
                    all_action_on_ops_for_simple_ops(*(static_cast<std::pair<Type_tag, uintptr_t>*>(*ptr)->second),  convert_to_number<uintptr_t>(second_arg),op, name_of_the_class_used_in)
                }
                    break;
                case Type_tag::long_double_tag:
                if constexpr (!std::is_same_v<uintptr_t, Op_two_type>)  {
                    all_action_on_ops_for_simple_ops(*(static_cast<std::pair<Type_tag, long double>*>(*ptr)->second),  long double{second_arg}, op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<long double, Op_two_type>)  {
                    all_action_on_ops_for_simple_ops(*(static_cast<std::pair<Type_tag, long double>*>(*ptr)->second), second_arg,op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<std::string, Op_two_type>)  {
                    all_action_on_ops_for_simple_ops(*(static_cast<std::pair<Type_tag, long double>*>(*ptr)->second),  convert_to_number<long double>(second_arg),op, name_of_the_class_used_in)
                }
                    break;
                case Type_tag::string_tag:
                if constexpr (!std::is_same_v<uintptr_t, Op_two_type>)  {
                    all_action_on_ops_for_simple_ops(*(static_cast<std::pair<Type_tag, std::string>*>(*ptr)->second),  std::to_string(second_arg),op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<long double, Op_two_type>)  {
                    all_action_on_ops_for_simple_ops(*(static_cast<std::pair<Type_tag, std::string>*>(*ptr)->second), std::to_string(second_arg),op, name_of_the_class_used_in)
                }
                else if(!std::is_same_v<std::string, Op_two_type>)  {
                    all_action_on_ops_for_simple_ops(*(static_cast<std::pair<Type_tag, std::string>*>(*ptr)->second),  second_arg,op, name_of_the_class_used_in)
                }
                break;
            }
            }

template<typename op, ternary_state op_action_type, typename name_of_the_class_used_in>
auto void_op_generator(void **ptr, void* second_arg) -> 
    typename std::conditional<op_action_type == _true, void, 
    typename std::conditional<op_action_type == _nuteral, bool, name_of_the_class_used_in>::type>::type 
{
    const Type_tag lhs_t = *static_cast<Type_tag*>(*ptr);
    const Type_tag rhs_t = *static_cast<Type_tag*>(second_arg);

    // Flattened VM-style dispatch table
    switch(produce_jump_index(lhs_t, rhs_t)) {

        // --- UINT_PTR LHS GROUP ---
        case produce_jump_index(Type_tag::uintptr_tag, Type_tag::uintptr_tag): {
            auto* lhs = static_cast<std::pair<Type_tag, uintptr_t>*>(*ptr);
            auto* rhs = static_cast<std::pair<Type_tag, uintptr_t>*>(second_arg);
            return all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(lhs->second, rhs->second);
        }
        case produce_jump_index(Type_tag::uintptr_tag, Type_tag::long_double_tag): {
            auto* lhs = static_cast<std::pair<Type_tag, uintptr_t>*>(*ptr);
            auto* rhs = static_cast<std::pair<Type_tag, long_double>*>(second_arg);
            return all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(lhs->second, static_cast<uintptr_t>(rhs->second));
        }
        case produce_jump_index(Type_tag::uintptr_tag, Type_tag::string_tag): {
            auto* lhs = static_cast<std::pair<Type_tag, uintptr_t>*>(*ptr);
            auto* rhs = static_cast<std::pair<Type_tag, fixed_size_strings_t>*>(second_arg);
            return all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(lhs->second, convert_to_number<uintptr_t>(rhs->second));
        }

        // --- LONG_DOUBLE LHS GROUP ---
        case produce_jump_index(Type_tag::long_double_tag, Type_tag::uintptr_tag): {
            auto* lhs = static_cast<std::pair<Type_tag, long_double>*>(*ptr);
            auto* rhs = static_cast<std::pair<Type_tag, uintptr_t>*>(second_arg);
            return all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(lhs->second, static_cast<long_double>(rhs->second));
        }
        case produce_jump_index(Type_tag::long_double_tag, Type_tag::long_double_tag): {
            auto* lhs = static_cast<std::pair<Type_tag, long_double>*>(*ptr);
            auto* rhs = static_cast<std::pair<Type_tag, long_double>*>(second_arg);
            return all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(lhs->second, rhs->second);
        }
        case produce_jump_index(Type_tag::long_double_tag, Type_tag::string_tag): {
            auto* lhs = static_cast<std::pair<Type_tag, long_double>*>(*ptr);
            auto* rhs = static_cast<std::pair<Type_tag, fixed_size_strings_t>*>(second_arg);
            return all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(lhs->second, convert_to_number<long_double>(rhs->second));
        }

        // --- FIXED_SIZE_STRINGS_T LHS GROUP ---
        case produce_jump_index(Type_tag::string_tag, Type_tag::uintptr_tag): {
            auto* lhs = static_cast<std::pair<Type_tag, fixed_size_strings_t>*>(*ptr);
            auto* rhs = static_cast<std::pair<Type_tag, uintptr_t>*>(second_arg);
            return all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(lhs->second, fixed_size_strings_t(std::to_string(rhs->second)));
        }
        case produce_jump_index(Type_tag::string_tag, Type_tag::long_double_tag): {
            auto* lhs = static_cast<std::pair<Type_tag, fixed_size_strings_t>*>(*ptr);
            auto* rhs = static_cast<std::pair<Type_tag, long_double>*>(second_arg);
            return all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(lhs->second, fixed_size_strings_t(std::to_string(rhs->second)));
        }
        case produce_jump_index(Type_tag::string_tag, Type_tag::string_tag): {
            auto* lhs = static_cast<std::pair<Type_tag, fixed_size_strings_t>*>(*ptr);
            auto* rhs = static_cast<std::pair<Type_tag, fixed_size_strings_t>*>(second_arg);
            return all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(lhs->second, rhs->second);
        }

        // --- NESTED / ARRAY DISPATCH ---
        case produce_jump_index(Type_tag::nested_type, Type_tag::nested_type): {
            auto& lhs_info = *static_cast<Extented_type_info*>(*ptr);
            auto& rhs_info = *static_cast<Extented_type_info*>(second_arg);
            
            if(lhs_info.size != rhs_info.size) throw std::string{"size mismatch"};

            auto* l_arr = reinterpret_cast<name_of_the_class_used_in*>(static_cast<char*>(*ptr) + sizeof(Extented_type_info));
            auto* r_arr = reinterpret_cast<name_of_the_class_used_in*>(static_cast<char*>(second_arg) + sizeof(Extented_type_info));

            if constexpr(op_action_type == _true) {
                for(uintptr_t i = 0; i < lhs_info.size; ++i)


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
                    break;
                case Type_tag::long_double_tag:
                    delete static_cast<std::pair<Extented_type_info, long double>*>(ptr);
                    break;
                case Type_tag::string_tag:
                    delete static_cast<std::pair<Extented_type_info, std::string>*>(ptr);
                    break;
                default:
                //assumes that the destructors of the derieved classes (hetrogenous array and extended types are empty)
                 Polymoprhic_extensible_engine* array= static_cast<Polymoprhic_extensible_engine*>(ptr+sizeof(Extented_type_info));
                for(int i=0; i<vector_containing_nested_type_info.length(); i++){
                ~array[i];
                }
                delete[] reinterpret_cast<char*>(ptr);
                break;
            }
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
                    break;
                    case Type_tag::long_double_tag:
                    ptr= static_cast<void*>(new std::pair<Type_tag, long double>
                    {Type_tag::long_double_tag,read_from_string<long double>(string_to_read_from, pos)});
                    break;
                    case Type_tag::string_tag:
                    ptr= static_cast<void*>(new std::pair<Type_tag, std::string>
                    {Type_tag::string_tag,read_from_string<std::string>(string_to_read_from, pos)});
                    break;
                    case Type_tag::heterogeneous_array:
                    Type_tag nested_tag= static_cast<Type_tag>(read_from_string<unsigned char>(string_to_read_from, pos));
                    ptr= static_cast<void*>(new std::pair<Type_tag, Hetrogenous_array>
                    {Type_tag::nested_type,{nested_tag, source, pos});
                    break;
                    case Type_tag::extended_types:
                        vector<Extented_type_info>* extra_info_for_extented_types;
                        switch(info.tag){
                        case Type_tag::vector_containing_types:
                            extra_info_for_extented_types= vector_containing_types[info.index];
                            break;
                        case Type_tag::type_in_map_tag:
                            extra_info_for_extented_types= map_containing_types[info.index];
                            break;
                        case Type_tag::type_in_hash_map_tag:
                            extra_info_for_extented_types= unordered_map_containing_types[info.index];
                            break;
                        default:
                            break;
                        }    
                        auto vec_size= vector_containing_nested_type_info.length();
                        uintptr_t array_size_in_bytes= sizeof(Polymoprhic_extensible_engine*)*vec_size; 
                        uintptr_t element_size_in_bytes=sizeof(Extended_types)*vec_size;
                        char *raw_mem= new char[array_size_in_bytes+element_size_in_bytes+sizeof(Extented_type_info)];
                        new (reinterpret_cast<Extented_type_info*>) Extented_type_info{Type_tag::nested_type, vec_size};
                        Polymoprhic_extensible_engine* array= reinterpret_cast<Polymoprhic_extensible_engine*>(raw_mem+sizeof(Extented_type_info));
                        Polymoprhic_extensible_engine* end= array+array_size_in_bytes;
                        for(int i=0; i<vec_size; i++){
                            array[i]=end+(i*element_size_in_bytes); 
                            new (array[i]) Extented_types{vector_containing_nested_type_info[i], source, location} };
                        }
                        ptr= static_cast<void*>(raw_mem);
                        break;
                    default:
                
                }
                
            }

    
            };
            struct Hetrogenous_array_type:public Polymoprhic_extensible_engine{
        //I know its not recommneded to provide "just in case aliases,but this is to show what is getting allocated in each case:
            using Nested_type= std::pair<Extented_type_info, Polymoprhic_extensible_engine*>;
            using Ordinary_type_int= std::pair<Type_tag, uintptr_t>;
            using Ordinary_type_double= std::pair<Type_tag, long double>;
            using Ordinary_type_string= std::pair<Type_tag, std::string>;
            using Ordinary_type_hetrogenous_array= std::pair<Type_tag, Hetrogenous_array>;
            using Hetrogenous_array= std::pair<Type_tag, Hetrogenous_array>;
            Hetrogenous_array_type(Type_tag info, const std::string& string_to_read_from, 
                std::string:size_type* pos )
            {
                switch(info){
                    case Type_tag::uintptr_tag:
                        ptr= static_cast<void*>(new std::pair<Type_tag, uintptr>{Type_tag::uintptr_tag,read_from_string<uintptr>(string_to_read_from, pos)});  
                        break;
                    case Type_tag::long_double_tag:
                        ptr= static_cast<void*>(new std::pair<Type_tag, long double>{Type_tag::long_double_tag,read_from_string<long double>(string_to_read_from, pos)});  
                        break;
                    case Type_tag::string_tag:
                        ptr= static_cast<void*>(new std::pair<Type_tag, std::string>{Type_tag::string_tag,read_from_string<std::string>(string_to_read_from, pos)});  
                        break;
                    case Type_tag::Extended_types:
                        ptr= static_cast<void*>(new std::pair<Type_tag, Extented_types>{Type_tag::extented_types,read_from_string<Extented_types>(string_to_read_from, pos)});  
                        break;
                    case Type_tag::hetrogenous_types:
                        uintptr_t size= read_from_string<uintptr_t>(string_to_read_from, pos);
                        uintptr_t array_size_in_bytes= sizeof(Polymoprhic_extensible_engine*)*size; 
                        uintptr_t element_size_in_bytes=sizeof(Hetrogenous_array_type)*size;
                        char *raw_mem= new char[array_size_in_bytes+element_size_in_bytes+sizeof(Extented_type_info)];
                        new (reinterpret_cast<Extented_type_info*>) Extented_type_info{Type_tag::nested_type, size};
                        Polymoprhic_extensible_engine* array= reinterpret_cast<Polymoprhic_extensible_engine*>(raw_mem+sizeof(Extented_type_info));
                        Polymoprhic_extensible_engine* end= array+array_size_in_bytes;
                        for(int i=0; i<size; i++){
                            array[i]=end+(i*element_size_in_bytes); 
                            new (array[i]) Hetrogenous_array_type{static_cast<Type_tag>(read_from_string<unsigned char>(string_to_read_from, pos)),source, location };
                        }
                        ptr= static_cast<void*>(raw_mem);
                        break;
                    default:
                        break;
            }
            };



            Polymoprhic_extensible_engine read_polymorphically_from_string(const std::string& string_to_read_from, std::string::size_type* pos) {
              
                   
                    
                

                

            }
            template <bool read_from_x_or_y>
            inline Polymoprhic_extensible_engine read_polymorphically_from_string(const std::string& x, const std::string& y, std::string::size_type* x_pos, std::string::size_type* y_pos) {
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























































