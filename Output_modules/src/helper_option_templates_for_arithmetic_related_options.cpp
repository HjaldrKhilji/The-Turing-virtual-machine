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
            struct Fixed_size_strings{
            std::string* ptr;
            inline Fixed_size_strings(std::string string_to_build_it_with): 
            ptr{    new std::string{  std::move( string_to_build_it_with )  }    } {}
            
            inline ~Fixed_size_strings(){
                delete ptr;
            }
            
            };
            inline std::string&& get(std::string&& a){
                return std::move(a);
            }            
            inline std::string& get(std::string& a){
                return a;
            }
            inline std::string&& get(Fixed_size_strings&& a){
                return std::move(*(a.ptr));
            }            
            inline std::string& get(Fixed_size_strings& a){
                return *(a.ptr);
            }
            constexpr common_size= sizeof(uintptr_t);
            template<typename T>
            struct Fancier_floats{
            using Underlying_t= T;
            Underlying_t *ptr;
            static Underlying_t double_null= NAN;
            inline Fancier_floats(Underlying_t raw_double_to_build_it_with): 
            ptr{   new Underlying_t{raw_double_to_build_it_with}   } {}
            inline Fancier_floats(Fancier_floats&& double_to_build_it_with): 
            ptr{   double_to_build_it_with.ptr   } {double_to_build_it_with.ptr=&double_null; }
            inline Fancier_floats(Fancier_floats& double_to_build_it_with): 
            ptr{   new Underlying_t{*double_to_build_it_with.ptr}   } { }
            inline  std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Hetrogenous_array_type>>
            Fancier_floats(){
                
            }
            inline ~Fancier_floats(){
                delete ptr;
            }

            };
            using Fixed_size_floats= std::conditional<(sizeof(long double)>common_size), long double,
                    std::conditional<(sizeof(double)>common_size), double, std::conditional<(sizeof(float)>common_size),
                    float, Fancier_floats<float>>>>//tries its best atleast, can never beat hardware sadly, too 
                    //many people work on that, and you cant tell everyone to follow one rule.
                    using long_double= Fancier_floats<long double>;
                using Fixed_size_strings_t== std::conditional<sizeof(std::string)<common_size, std::string>;
                using Hetrogenous_array_type=Hetrogenous_array_type;
                enum class Type_tag : unsigned char {
                     /* --- [ 00 - 01 ] High-Operand Specialized Tags --- */
                    string_tag_for_15_plus_operand_ops          = 0,
                    uintptr_tag_for_15_plus_operand_ops         = 1,
                    
                    /* --- [ 02 - 06 ] Scalar Primitive Types --- */
                    long_double_tag_implementation_defined_size = 2,
                    eight_byte_double_tag                        = 3,
                    uintptr_tag                                 = 4,
                    string_tag                                  = 5,
                    intptr_tag                                  = 6,
                    
                    /* --- [ 07 - 12 ] Contiguous & Dynamic Containers --- */
                    vector_string                               = 7,
                    vector_uintptr                              = 8,
                    vector_intptr                               = 9,
                    vector_double                               = 10,
                    vector_long_double_tag_implementation_defined_size = 11,
                    nested_type_with_dynamic_container          = 12,
                    
                    /* --- [ 13 - 19 ] System & Concurrency Handles --- */
                    object_info                                 = 13,
                    atomic_nested_owning_type                   = 14,
                    semaphore                                   = 15,
                    lock                                        = 16,
                    process_executioner                         = 17,
                    socket_executioner                          = 18,
                    jthread_nested_machine                      = 19,
                    
                    /* --- [ 20 - 24 ] Computational & Linking Ops --- */
                    reference_to_vecotr_of_nested_for_gpu_ops   = 20,
                    encryption                                  = 21,
                    decryption                                  = 22,
                    predict                                     = 23,
                    linked                                      = 24,
                    
                    /* --- [ 25 - 29 ] Interface, Events & Extensibility --- */
                    gui                                         = 25,
                    capture_event                               = 26,
                    confirm_event                               = 27,
                    user_defined_binary_code_ops                = 28,
                    other                                       = 29
                
                    // not all of them would be implemented right now, like it would be a step by step process, 
                    // but all of them will have a respective entry until they are implemented
                };
                      
                enum class Type_tag_for_input : unsigned char {
                    /* --- High-Operand Specialized Tags --- */
                    string_tag_for_15_plus_operand_ops          = 0,
                    uintptr_tag_for_15_plus_operand_ops         = 1,
                    intptr_tag_for_15_plus_operand_ops          = 2,
                    long_double_tag_implementation_defined_size_for_15_plus_operand_ops  = 3,
                    eight_byte_double_tag_for_15_plus_operand_ops =4,
                    /* --- Scalar Primitive Types --- */
                    eight_byte_double_tag,
                    uintptr_tag,
                    string_tag,
                    intptr_tag,
                    
                    /* --- Contiguous & Dynamic Containers --- */
                    vector_string,
                    vector_uintptr,
                    vector_intptr,
                    vector_double,
                    vector_long_double_tag_implementation_defined_size,
                    nested_type_with_dynamic_container,
                    
                    /* --- System & Concurrency Handles --- */
                    object_info,
                    atomic_nested_owning_type,
                    semaphore,
                    lock,
                    process_executioner,
                    socket_executioner,
                    jthread_nested_machine,
                    
                    /* --- Computational & Linking Ops --- */
                    reference_to_vecotr_of_nested_for_gpu_ops,
                    encryption,
                    decryption,
                    predict,
                    linked,
                    
                    /* --- Interface, Events & Extensibility --- */
                    gui,
                    capture_event,
                    confirm_event,
                    user_defined_binary_code_ops,
                    other,
                    
                    /* --- Container Nesting (Gateway Tags) --- */
                    array_nested_type_vector,
                    array_nested_type_deque,
                    array_nested_type_list,
                    array_nested_type_forward_list,
                    array_nested_type_set,
                    array_nested_type_unordered_set,
                    array_nested_type_multi_set,
                    array_nested_type_unordered_multi_unordered_set,
                    array_nested_type_redis_map,
                    heterogeneous_array,
                    type_in_vector_tag,
                    type_in_deque_tag,
                    type_in_map_tag,
                    type_in_multi_map_tag,
                    type_in_hash_map_tag,
                    type_in_multi_hash_map_tag,
                    type_in_list,
                    type_in_forward_list
            };
            constexpr inline unsigned char produce_jump_index(Type_tag type_x, Type_tag type_y){
                (static_cast<unsigned char>(type)>>4)+type_y;
            }
            sturct Extented_type_info{
                Type_tag tag;
                uintptr_t index;
            }
            
            std::vector<std::vector<Extented_type_info>> vector_containing_types;
            std::deque<std::vector<Extented_type_info>> deque_containing_types;
            std::list<std::vector<Extented_type_info>> list_containing_types;
            std::forward_list<std::vector<Extented_type_info>> forward_list_containing_types;
            std::map<uintptr_t,std::vector<Extented_type_info>> map_containing_types;
            std::multimap<uintptr_t,std::vector<Extented_type_info>> multimap_containing_types;
            std::unordered_map<uintptr_t,std::vector<Extented_type_info>> hash_map_containing_types;
            std::unordered_multimap<uintptr_t,std::vector<Extented_type_info>> hash_multimap_containing_types;
            std::array<std::vector<Extented_type_info>, 100> array_containing_types{{}};
            struct nested_type_info{
                Type_tag_for_input tag;
                void* ptr;
            };
            
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
            template<typename Op, ternary_state op_action_type, typename Name_of_the_class_used_in, typename Lhs_t, typename Rhs_t>
            inline  std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Hetrogenous_array_type>> 
            all_action_on_ops_for_simple_ops_on_void_pointers(name_of_the_class_used_in lhs,name_of_the_class_used_in rhs){
            all_action_on_ops_for_simple_ops<op, op_action_type, name_of_the_class_used_in>(
            static_cast<Lhs_t>*>(*(lhs->ptr)),
            static_cast<Rhs_t>*>(*(rhs->ptr))
            );
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
#define ALiaSES_f0R_JuMPEnTeRYGeNAraT0r()\
using intptr_tag = intptr_t;\
using uintptr_tag = uintptr_t;\
using long_double_tag = long_double;\
using string_tag = Fixed_size_strings_t;\
using vector_intptr = std::vector<intptr_t>;\
using vector_uintptr = std::vector<uintptr_t>;\
using vector_double = std::vector<long_double>;\
using vector_string = std::vector<Fixed_size_strings_t>;
#define JuMPEnTeRYGeNAraT0r(op,
op_action_type,
name_of_the_class_used_in, 
only_arg_type_for_first_paremeter,
_1_first_type_arg_for_second_parameter,
_2_second_type_arg_for_second_parameter,
_3_third_type_arg_for_second_parameter,
_4_forth_type_arg_for_second_parameter,
_5_fifth_type_arg_for_second_parameter,
_6_sixth_type_arg_for_second_parameter,
_7_seventh_type_arg_for_second_parameter,
_8_eighth_type_arg_for_second_paremeter,
ptr_of_first_arg,
ptr_of_second_type)\
        case produce_jump_index(Type_tag::uintptr_tag, Type_tag::uintptr_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, uintptr_t, uintptr_t>(ptr, second_arg);
        
        case produce_jump_index(Type_tag::uintptr_tag, Type_tag::long_double_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, uintptr_t, long_double>(ptr, second_arg);
        
        case produce_jump_index(Type_tag::uintptr_tag, Type_tag::string_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, uintptr_t, Fixed_size_strings_t>(ptr, second_arg);




template<typename op, ternary_state op_action_type, typename name_of_the_class_used_in>
auto void_op_generator(void **ptr, void* second_arg) -> 
    typename std::conditional<op_action_type == _true, void, 
    typename std::conditional<op_action_type == _nuteral, bool, name_of_the_class_used_in>::type>::type 
{



 switch(produce_jump_index(*static_cast<Type_tag*>(*ptr), *static_cast<Type_tag*>(second_arg))) 
{        using Type_tag;
         ALiaSES_f0R_JuMPEnTeRYGeNAraT0r;
        // --- UINT_PTR LHS GROUP ---
        case produce_jump_index(Type_tag::uintptr_tag, Type_tag::uintptr_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, uintptr_t, uintptr_t>(ptr, second_arg);
        
        case produce_jump_index(Type_tag::uintptr_tag, Type_tag::long_double_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, uintptr_t, long_double>(ptr, second_arg);
        
        case produce_jump_index(Type_tag::uintptr_tag, Type_tag::string_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, uintptr_t, Fixed_size_strings_t>(ptr, second_arg);

        // --- LONG_DOUBLE LHS GROUP ---
        case produce_jump_index(Type_tag::long_double_tag, Type_tag::uintptr_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, long_double, uintptr_t>(ptr, second_arg);
        
        case produce_jump_index(Type_tag::long_double_tag, Type_tag::long_double_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, long_double, long_double>(ptr, second_arg);
        
        case produce_jump_index(Type_tag::long_double_tag, Type_tag::string_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, long_double, Fixed_size_strings_t>(ptr, second_arg);

        // --- Fixed_size_strings_T LHS GROUP ---
        case produce_jump_index(Type_tag::string_tag, Type_tag::uintptr_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, Fixed_size_strings_t, uintptr_t>(ptr, second_arg);
        
        case produce_jump_index(Type_tag::string_tag, Type_tag::long_double_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, Fixed_size_strings_t, long_double>(ptr, second_arg);
        
        case produce_jump_index(Type_tag::string_tag, Type_tag::string_tag):
            return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, name_of_the_class_used_in, Fixed_size_strings_t, Fixed_size_strings_t>(ptr, second_arg);

        // --- NESTED / ARRAY DISPATCH ---
        case produce_jump_index(Type_tag::nested_type, Type_tag::nested_type): {
            auto& lhs_info = *static_cast<Extented_type_info*>(*ptr);
            auto& rhs_info = *static_cast<Extented_type_info*>(second_arg);
            
            if(lhs_info.size != rhs_info.size) throw std::string{"size mismatch"};

            auto* l_arr = reinterpret_cast<name_of_the_class_used_in*>(static_cast<char*>(*ptr) + sizeof(Extented_type_info));
            auto* r_arr = reinterpret_cast<name_of_the_class_used_in*>(static_cast<char*>(second_arg) + sizeof(Extented_type_info));

            if constexpr(op_action_type == _true) {
                for(uintptr_t i = 0; i < lhs_info.size; ++i) op(r_arr[i], l_arr[i]);
            } else if constexpr (op_action_type == _nuteral) {
                for(uintptr_t i = 0; i < lhs_info.size; ++i) {
                    if(!op(r_arr[i], l_arr[i])) return false;
                }
                return true;
            } else {
                for(uintptr_t i = 0; i < lhs_info.size; ++i) op(r_arr[i], l_arr[i]);
                return name_of_the_class_used_in{Type_tag::nested_type, *ptr};
            }
        }
        break;
        //mismatch
        default:
            throw std::string{"operand mismatch"};
    }
}   


            
            struct Polymoprhic_extensible_engine{

            Type_tag tag;
            void *ptr;
            

            constexpr Polymoprhic_extensible_engine(Type_tag tag_of_type_to_construct_from,void* source):
            tag{tag_of_type_to_construct_from}, ptr{source}{}


            template <Type_tag tag_of_type_to_construct_from>
            inline Polymoprhic_extensible_engine(void* source):Polymoprhic_extensible_engine{
            Polymoprhic_extensible_engine{tag_of_type_to_construct_from, source}
            } {}


            inline Polymoprhic_extensible_engine(tag_of_type_to_construct_from source){
               switch(source.tag){
                   /* --- High-Operand Specialized Tags --- */
                    case Type_tag::string_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = std::string;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::string_tag_for_15_plus_operand_ops;
                        break;
                    }
                    case Type_tag::uintptr_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = uintptr_t;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::uintptr_tag_for_15_plus_operand_ops;
                        break;
                    }
                    case Type_tag::intptr_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = intptr_t;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::intptr_tag_for_15_plus_operand_ops;
                        break;
                    }
                    case Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops: {
                        using Source_and_target_type = long double;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops;
                        break;
                    }
                    case Type_tag::eight_byte_double_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = double;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::eight_byte_double_tag_for_15_plus_operand_ops;
                        break;
                    }
                
                    /* --- Scalar Primitive Types --- */
                    case Type_tag::eight_byte_double_tag: {
                        using Source_and_target_type = double;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::eight_byte_double_tag;
                        break;
                    }
                    case Type_tag::uintptr_tag: {
                        using Source_and_target_type = uintptr_t;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::uintptr_tag;
                        break;
                    }
                    case Type_tag::string_tag: {
                        using Source_and_target_type = std::string;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::string_tag;
                        break;
                    }
                    case Type_tag::intptr_tag: {
                        using Source_and_target_type = intptr_t;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::intptr_tag;
                        break;
                    }
                
                    /* --- Contiguous & Dynamic Containers --- */
                    case Type_tag::vector_string: {
                        using Source_and_target_type = std::vector<std::string>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::vector_string;
                        break;
                    }
                    case Type_tag::vector_uintptr: {
                        using Source_and_target_type = std::vector<uintptr_t>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::vector_uintptr;
                        break;
                    }
                    case Type_tag::vector_intptr: {
                        using Source_and_target_type = std::vector<intptr_t>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::vector_intptr;
                        break;
                    }
                    case Type_tag::vector_double: {
                        using Source_and_target_type = std::vector<double>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::vector_double;
                        break;
                    }
                    case Type_tag::vector_long_double_tag_implementation_defined_size: {
                        using Source_and_target_type = std::vector<long double>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::vector_long_double_tag_implementation_defined_size;
                        break;
                    }
                    case Type_tag::nested_type_with_dynamic_container:       
                        nested_type_info underlying_obj= *(static_cast<nested_type_info*>(source.ptr));
                        switch(underlying_obj->tag){
                            case Type_tag_for_input::vector_containing_types:
                                using source_and_target_type= std::vector<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container,
                                ptr = random_access_copy<source_and_target_type, Type_tag_for_input::vector_containing_types>(underlying_obj->ptr)};
                                break;
                            case Type_tag_for_input::type_in_deque_tag:
                                using source_and_target_type= std::deque<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container,
                                random_access_copy<source_and_target_type, Type_tag_for_input::type_in_deque_tag>(underlying_obj->ptr);
                                break;
                            case Type_tag_for_input::type_in_list:
                                using source_and_target_type= std::list<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container,
                                random_access_copy<source_and_target_type, Type_tag_for_input::type_in_list>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_forward_list:
                                using source_and_target_type= std::forward_list<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container,
                                random_access_copy<source_and_target_type, Type_tag_for_input::type_in_forward_list>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_map_tag:
                                using source_and_target_type= std::map<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container,
                                random_access_copy<source_and_target_type, Type_tag_for_input::type_in_map_tag>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_multi_map_tag:
                                using source_and_target_type= std::multimap<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container,
                                random_access_copy<source_and_target_type, Type_tag_for_input::type_in_multi_map_tag>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_hash_map_tag:
                                using source_and_target_type= std::unordered_map<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container,
                                random_access_copy<source_and_target_type, Type_tag_for_input::type_in_hash_map_tag>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_multi_hash_map_tag:
                                using source_and_target_type= std::unordered_multimap<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container,
                                random_access_copy<source_and_target_type, Type_tag_for_input::type_in_multi_hash_map_tag>(underlying_obj->ptr);
                            default:
                                throw std::string{"Invalid Container Tag"};
                                break;
                        }
                     //the rest of the types are currently unsupported :(
                     //(got to finish the base of this project as fast as I can cuz i spend too much time)   
                    default:
                        throw std::string{"Invalid Type Tag"};
                        break;

                }
            }
            template<typename Underlying_container_specialization, Type_tag_for_input tag>
            requires{//the concept is weather the expression below works or not
            typename std::common_type_t
                <std::iterator_traits<Underlying_container_specialization>::iterator, std::input_iterator_tag>;
            }
                static inline void*  copy_nested(void* source){
                    underlying_container_specialization& formated_source= 
                    *(static_cast<underlying_container_specialization*>(source));
                    //NOTE: underlying_container_specialization is a container type.
                    underlying_container_specialization& destination_data= *(new underlying_container_specialization(formated_source.size()));

                    std::copy(std::formated_source.begin(), formated_source.end(), destination_data.begin(), 
                        [](value_type source_ptr){
                            return Polymoprhic_extensible_engine(source_ptr);
                        
                    });    
                    return static_cast<void*>(new nested_type_info{tag, static_cast<void*>(destination_data)}); 

                }
            template <typename op, typename op, ternary_state op_action_type>
            requires std::is_arithmetic_v<Op_two_type> || std::is_same_v<std:string, Op_two_type>
            inline std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Polymoprhic_extensible_engine>>
            void_operator_generator(Op_two_type second_arg) {
                void_operator_generator<Op_two_type, op, op_action_type, Polymoprhic_extensible_engine>, op_action_type(&ptr,second_arg, &tag);
            }
                    
            template<typename op, ternary_state op_action_type>
            inline std::contional<op_action_type==_true, void,  std::contional<op_action_type==_nuteral, bool, Polymoprhic_extensible_engine>> 
            void_op_generator(Polymoprhic_extensible_engine second_arg){
                void_op_generator<op, op_action_type, Polymoprhic_extensible_engine>(&ptr, second_arg.ptr, &tag);
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
                        case Type_tag::type_in_deque_tag:
                            extra_info_for_extented_types= deque_containing_types[info.index];
                            break;
                        case Type_tag::type_in_list:
                            extra_info_for_extented_types= *(std::find(list_containing_types.begin(), 
                            list_containing_types.end(), info.index));
                            break;
                        case Type_tag::type_in_forward_list:
                            extra_info_for_extented_types= *(std::find(forward_list_containing_types.begin(), 
                            forward_list_containing_types.end(), info.index));
                            break;                        
                        case Type_tag::type_in_list_parallel:
                            extra_info_for_extented_types= *(std::find(,std::execution::parallel_policy,
                            forward_list_containing_types.begin(),  forward_list_containing_types.end(), info.index));                            break;
                        case Type_tag::type_in_forward_list_parallel:
                            extra_info_for_extented_types= *(std::find(std::execution::parallel_policy,
                            forward_list_containing_types.begin(), forward_list_containing_types.end(), info.index));                            break;
                        case Type_tag::type_in_map_tag:
                            extra_info_for_extented_types= map_containing_types[info.index];
                            break;
                        case Type_tag::type_in_multi_map_tag:
                            extra_info_for_extented_types= multimap_containing_types[info.index];
                            break;
                        case Type_tag::type_in_hash_map_tag:
                            extra_info_for_extented_types= hash_map_containing_types[info.index];
                            break;
                        case Type_tag::type_in_multi_hash_map_tag:
                            extra_info_for_extented_types= unordered_map_containing_types[info.index];
                            break;
                        case Type_tag::type_in_array:
                            extra_info_for_extented_types= array_containing_types[info.index];
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




































































