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

                template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
                inline typename std::conditional<op_action_type == true, void, bool>
                all_action_on_ops_for_simple_ops_on_void_pointers(void* lhs, void* rhs) {
                    //this specialization is at the top in the chain of arethimetic
                    auto* l = static_cast<Lhs_t*>(lhs);
                    auto* r = static_cast<Rhs_t*>(rhs);
                
                    if constexpr (op_action_type == true) {
                        Op{}(l, r);
                    }
                    else {
                        return Op{}(l, r);;
                    }
                }
            template<typename T>
            concept Is_complex_userdefined = require(Lhs_t a){
                {Lhs_t.ptr}->std::same_as<void>;
                {Lhs_t.tag}->std::same_as<Type_tag>;
            };
                 
            template<typename Op, bool op_action_type, Is_complex_userdefined Lhs_t, Is_complex_userdefined Rhs_t>
            inline typename std::conditional<op_action_type == true, void, bool>  
            op_scalar_or_collection_with_collection(Lhs_t& lhs,Rhs_t& rhs){
                    
            }                 
            template<typename Op, bool op_action_type, Is_complex_userdefined Lhs_t, typename Rhs_t>
            inline typename std::conditional<op_action_type == true, void, bool>  
            op_scalar_or_collection_with_collection(Lhs_t& lhs,Rhs_t& rhs){
                    
            }
            template<typename Op, bool op_action_type, typename Lhs_t, Is_complex_userdefined Rhs_t>
            inline typename std::conditional<op_action_type == true, void, bool>  
            op_scalar_or_collection_with_collection(Lhs_t& lhs,Rhs_t& rhs){
                rhs.void_op_generator<>
            }
            template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
            requires{//the concept is weather the expression below works or not
            typename std::common_type_t
            <std::iterator_traits<Lhs::iterator>::iterator_category, std::input_iterator_tag>;
            }
            inline typename std::conditional<op_action_type == true, void, bool>  
                op_scalar_or_collection_with_collection(Lhs_t& lhs,Rhs_t& rhs){

                    if constexpr (op_action_type == true) {
                    for(auto x: formated_lhs) {
                        Op{}(formated_rhs, x);
                    }
                    }
                    else {
                    for(auto x: formated_lhs) {
                        if(!Op{}(formated_rhs, x)){
                            return false;
                        }
                    }
                    return true;
                    }

                    }


            template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
            requires{//the concept is weather the expression below works or not
            typename std::common_type_t
            <std::iterator_traits<Rhs_t::iterator>::iterator_category, std::input_iterator_tag>;
            }
                inline typename std::conditional<op_action_type == true, void, bool>  
                    op_scalar_with_collection(void* lhs,void* rhs){
                        
                    auto & formated_rhs= 
                    *(static_cast<Rhs_t*>(rhs));
                    auto& formated_lhs= *( static_cast<Lhs_t*>(lhs) );

                    if constexpr (op_action_type == true) {
                    for(auto x: formated_rhs) {
                        op_scalar_or_collection_with_collection<Op, op_action_type>(formated_lhs, x);
                    }
                    }
                    else {
                    for(auto x: formated_rhs) {
                        if(!op_scalar_or_collection_with_collection<Op, op_action_type>(formated_lhs, x)){
                            return false;
                        }
                    }
                    return true;
                    }
                    
                }

                template<typename Op, ternary_state op_action_type, typename Rhs_t, typename Lhs_t>
                inline typename std::conditional<op_action_type == true, void, bool>
                all_action_on_ops_for_simple_ops_on_void_pointers_collections(void* lhs, void* rhs) {
                nested_type_info underlying_obj= *(static_cast<nested_type_info*>(ptr_of_second_arg));
                switch(underlying_obj->tag){
                case Type_tag_for_input::vector_containing_types:
                    using source_and_target_type= std::vector<Polymoprhic_extensible_engine>;
                    op_scalar_with_collection<Op, op_action_type, Name_of_the_class_used_in,source_tag, Rhs_t, Lhs_t>(underlying_obj->ptr)};
                    break;
                case Type_tag_for_input::type_in_deque_tag:
                    using source_and_target_type= std::deque<Polymoprhic_extensible_engine>;
                    op_scalar_with_collection<Op, op_action_type, Name_of_the_class_used_in,source_tag, Rhs_t, Lhs_t>(underlying_obj->ptr);
                    break;
                case Type_tag_for_input::type_in_list:
                    using source_and_target_type= std::list<Polymoprhic_extensible_engine>;
                    op_scalar_with_collection<Op, op_action_type, Name_of_the_class_used_in,source_tag, Rhs_t, Lhs_t>(underlying_obj->ptr);
                case Type_tag_for_input::type_in_forward_list:
                    using source_and_target_type= std::forward_list<Polymoprhic_extensible_engine>;
                    op_scalar_with_collection<Op, op_action_type, Name_of_the_class_used_in,source_tag, Rhs_t, Lhs_t>(underlying_obj->ptr);
                case Type_tag_for_input::type_in_map_tag:
                    using source_and_target_type= std::map<Polymoprhic_extensible_engine>;
                    op_scalar_with_collection<Op, op_action_type, Name_of_the_class_used_in,source_tag, Rhs_t, Lhs_t>(underlying_obj->ptr);
                case Type_tag_for_input::type_in_multi_map_tag:
                    using source_and_target_type= std::multimap<Polymoprhic_extensible_engine>;
                    op_scalar_with_collection<Op, op_action_type, Name_of_the_class_used_in,source_tag, Rhs_t, Lhs_t>(underlying_obj->ptr);
                case Type_tag_for_input::type_in_hash_map_tag:
                    using source_and_target_type= std::unordered_map<Polymoprhic_extensible_engine>;
                    op_scalar_with_collection<Op, op_action_type, Name_of_the_class_used_in,source_tag, Rhs_t, Lhs_t>(underlying_obj->ptr);
                case Type_tag_for_input::type_in_multi_hash_map_tag:
                    using source_and_target_type= std::unordered_multimap<Polymoprhic_extensible_engine>;
                    op_scalar_with_collection<Op, op_action_type, Name_of_the_class_used_in,source_tag, Rhs_t, Lhs_t>(underlying_obj->ptr);
                default:
                    throw std::string{"Invalid Container Tag"};
                    break;
                }
            #define JuMPEnTeRYGeNAraT0r(op, \
                            op_action_type, \
                            name_of_the_class_used_in, \
                            only_arg_type_for_first_paremeter, \
                            only_tag_for_first_paremeter, \
                            ptr_of_first_arg, \
                            ptr_of_second_arg) \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::string_tag_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::string>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::uintptr_tag_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, uintptr_t>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::intptr_tag_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, intptr_t>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, long double>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::eight_byte_double_tag_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, double>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::eight_byte_double_tag): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, double>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::uintptr_tag): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, uintptr_t>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::string_tag): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::string>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::intptr_tag): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, intptr_t>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_string): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<std::string>>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_uintptr): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<uintptr_t>>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_intptr): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<intptr_t>>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_double): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<double>>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_long_double_tag_implementation_defined_size): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<long double>>(ptr_of_first_arg, ptr_of_second_arg); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::nested_type_with_dynamic_container): \ 
        all_action_on_ops_for_simple_ops_on_void_pointers_collections<op, op_action_type, only_arg_type_for_first_paremeter, double>(ptr_of_first_arg, ptr_of_second_arg)



        


            
            struct Polymoprhic_extensible_engine{

            Type_tag tag;
            void *ptr;
            

            constexpr Polymoprhic_extensible_engine(Type_tag tag_of_type_to_construct_from,void* source):
            tag{tag_of_type_to_construct_from}, ptr{source}{}


            template<typename T, Type_tag_for_input tag>
            constexpr Polymoprhic_extensible_engine(T* source):Polymoprhic_extensible_engine{
            Polymoprhic_extensible_engine{tag, source->ptr}
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
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = random_access_copy<source_and_target_type, Type_tag_for_input::vector_containing_types>(underlying_obj->ptr)};
                                break;
                            case Type_tag_for_input::type_in_deque_tag:
                                using source_and_target_type= std::deque<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = random_access_copy<source_and_target_type, Type_tag_for_input::type_in_deque_tag>(underlying_obj->ptr);
                                break;
                            case Type_tag_for_input::type_in_list:
                                using source_and_target_type= std::list<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = random_access_copy<source_and_target_type, Type_tag_for_input::type_in_list>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_forward_list:
                                using source_and_target_type= std::forward_list<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = random_access_copy<source_and_target_type, Type_tag_for_input::type_in_forward_list>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_map_tag:
                                using source_and_target_type= std::map<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = random_access_copy<source_and_target_type, Type_tag_for_input::type_in_map_tag>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_multi_map_tag:
                                using source_and_target_type= std::multimap<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = random_access_copy<source_and_target_type, Type_tag_for_input::type_in_multi_map_tag>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_hash_map_tag:
                                using source_and_target_type= std::unordered_map<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = random_access_copy<source_and_target_type, Type_tag_for_input::type_in_hash_map_tag>(underlying_obj->ptr);
                            case Type_tag_for_input::type_in_multi_hash_map_tag:
                                using source_and_target_type= std::unordered_multimap<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = random_access_copy<source_and_target_type, Type_tag_for_input::type_in_multi_hash_map_tag>(underlying_obj->ptr);
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
                <std::iterator_traits<Underlying_container_specialization::iterator>::iterator_category, std::input_iterator_tag>;
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

                    
                template<typename Op, ternary_state op_action_type>
                inline typename std::conditional<op_action_type == true, void, bool>
                    void_op_generator(Polymoprhic_extensible_engine second_arg){
                    switch(tag){
                        /* --- Full Outer Dispatch Table --- */
                    
                        // 00 - 01: High-Operand Specialized
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, std::string, ptr_of_first_arg, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, uintptr_t, ptr_of_first_arg, ptr_of_second_arg)
                        
                        // 02 - 06: Scalar Primitives
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, long double, ptr_of_first_arg, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, double, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, uintptr_t, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, std::string, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, intptr_t, ptr_of_second_arg)
                        
                        // 07 - 12: Containers
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<std::string>, ptr_of_first_arg, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<uintptr_t>, ptr_of_first_arg, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<intptr_t>, ptr_of_first_arg, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<double>, ptr_of_first_arg, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<long double>, ptr_of_first_arg, ptr_of_second_arg)
                        JuMPEnTeRYGeNAraT0r(op, op_action_type, void*, ptr_of_first_arg, ptr_of_second_arg)
                        
                        default:
                            throw std::string{"Unimplemented type"};
                        
                        }    
                    }
            ~Polymoprhic_extensible_engine(){
                switch(tag) {
                    /* --- [ 00 - 01 ] High-Operand Specialized Tags (DESTRUCTIVE) --- */
                    case Type_tag::string_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = std::string;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::uintptr_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = uintptr_t;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::intptr_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = intptr_t;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops: {
                        using Source_and_target_type = long double;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::eight_byte_double_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = double;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }

                    /* --- [ 02 - 06 ] Scalar Primitive Types (DESTRUCTIVE) --- */
                    case Type_tag::eight_byte_double_tag: {
                        using Source_and_target_type = double;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::uintptr_tag: {
                        using Source_and_target_type = uintptr_t;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::string_tag: {
                        using Source_and_target_type = std::string;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::intptr_tag: {
                        using Source_and_target_type = intptr_t;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }

                    /* --- [ 07 - 12 ] Contiguous & Dynamic Containers (DESTRUCTIVE) --- */
                    case Type_tag::vector_string: {
                        using Source_and_target_type = std::vector<std::string>;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::vector_uintptr: {
                        using Source_and_target_type = std::vector<uintptr_t>;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::vector_intptr: {
                        using Source_and_target_type = std::vector<intptr_t>;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::vector_double: {
                        using Source_and_target_type = std::vector<double>;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }
                    case Type_tag::vector_long_double_tag_implementation_defined_size: {
                        using Source_and_target_type = std::vector<long double>;
                        delete (static_cast<Source_and_target_type*>(ptr));
                        break;
                    }

                    /* --- Nested Types (DESTRUCTIVE) --- */
                    case Type_tag::nested_type_with_dynamic_container: {
                        auto* underlying_obj = static_cast<nested_type_info*>(ptr);
                        
                        switch(underlying_obj->tag) {
                            case Type_tag_for_input::vector_containing_types: {
                                using container_type = std::vector<Polymoprhic_extensible_engine>;
                                delete (static_cast<container_type*>(underlying_obj->ptr));
                                break;
                            }
                            case Type_tag_for_input::type_in_deque_tag: {
                                using container_type = std::deque<Polymoprhic_extensible_engine>;
                                delete (static_cast<container_type*>(underlying_obj->ptr));
                                break;
                            }
                            case Type_tag_for_input::type_in_list: {
                                using container_type = std::list<Polymoprhic_extensible_engine>;
                                delete (static_cast<container_type*>(underlying_obj->ptr));
                                break;
                            }
                            case Type_tag_for_input::type_in_forward_list: {
                                using container_type = std::forward_list<Polymoprhic_extensible_engine>;
                                delete (static_cast<container_type*>(underlying_obj->ptr));
                                break;
                            }
                            case Type_tag_for_input::type_in_map_tag: {
                                using container_type = std::map<uintptr_t, Polymoprhic_extensible_engine>;
                                delete (static_cast<container_type*>(underlying_obj->ptr));
                                break;
                            }
                            case Type_tag_for_input::type_in_multi_map_tag: {
                                using container_type = std::multimap<uintptr_t, Polymoprhic_extensible_engine>;
                                delete (static_cast<container_type*>(underlying_obj->ptr));
                                break;
                            }
                            case Type_tag_for_input::type_in_hash_map_tag: {
                                using container_type = std::unordered_map<uintptr_t, Polymoprhic_extensible_engine>;
                                delete (static_cast<container_type*>(underlying_obj->ptr));
                                break;
                            }
                            case Type_tag_for_input::type_in_multi_hash_map_tag: {
                                using container_type = std::unordered_multimap<uintptr_t, Polymoprhic_extensible_engine>;
                                delete (static_cast<container_type*>(underlying_obj->ptr));
                                break;
                            }
                            default:
                                break; 
                        }
                        delete underlying_obj;
                        break;
                    }

                    default:
                        throw std::string{"Invalid Type Tag during deletion"};
                        break;
                }
            }
            }

           
            };
            struct Extented_types:public Polymoprhic_extensible_engine{

            Extented_types(const Extented_type_info& info, const std::string& string_to_read_from, 
                std::string:size_type* pos )
            {
                
            }
           
            };
            struct Hetrogenous_array_type:public Polymoprhic_extensible_engine{

            Hetrogenous_array_type(Type_tag info, const std::string& string_to_read_from, 
                std::string:size_type* pos )
            {
            
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








































































