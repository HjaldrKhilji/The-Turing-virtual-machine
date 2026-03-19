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
                    other
                
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
                return (static_cast<unsigned char>(type)>>4)+type_y;
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
            enum class thread_policy : unsigned char {
            unsequenced_exec,
            unsequenced_parrallel_exec
            }; //notice that all operations are unsequenced
            struct Nested_type_info{
                Type_tag_for_input tag;
                bool execution_policy;
                void* ptr;
            };

                template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
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
                 
                template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
            inline typename std::conditional<op_action_type == true, void, bool>  
            op_scalar_or_collection_with_collection(Lhs_t& lhs,Rhs_t& rhs){
                    
            }                 
                template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
            inline typename std::conditional<op_action_type == true, void, bool>  
            op_scalar_or_collection_with_collection(Lhs_t& lhs,Rhs_t& rhs){
                    
            }
                template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
            inline typename std::conditional<op_action_type == true, void, bool>  
            op_scalar_or_collection_with_collection(Lhs_t& lhs,Rhs_t& rhs){
                rhs.void_op_generator<>
            }
                template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
            requires{//the concept is weather the expression below works or not
            typename std::common_type_t
            <std::iterator_traits<Lhs::iterator>::iterator_category, std::input_iterator_tag>;
            }
            inline typename std::conditional<op_action_type == true, void, bool>  
                op_scalar_or_collection_with_collection(Lhs_t* lhs,Rhs_t& rhs){

                    if constexpr (op_action_type == true) {
                    for(auto x: *lhs) {
                        lhs->void_op_generator<Op, op_action_type>(*rhs);
                    }
                    }
                    else {
                    for(auto x: *lhs) {
                        if(!lhs->void_op_generator<Op, op_action_type>(*rhs)){
                            return false;
                        }
                    }
                    return true;
                    }

                    }
                        template<Op, op_action_type, Lhs_tag, Rhs_t, Lhs_t>



            template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
            requires{//the concept is weather the expression below works or not
            typename std::common_type_t
            <std::iterator_traits<Lhs_t::iterator>::iterator_category, std::input_iterator_tag>;
            }
            inline typename std::conditional<op_action_type == true, void, bool>  
                op_scalar_or_collection_with_collection(Lhs_t* lhs,const Rhs_t& rhs){
                    if constexpr (op_action_type == true) {
                    switch(source->execution_policy){
                        case thread_policy::unsequenced_exec:
                            return std::for_each(std::execution::unseq , lhs->begin(), lhs->end(),
                                [](Lhs_t::value_type lhs_sub_element){
                                    return op_scalar_or_collection_with_collection<Op, true, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs);
                            });
                        case thread_policy::unsequenced_parrallel_exec:
                            return std::for_each(std::execution::par_unseq , lhs->begin(), lhs->end(),
                                [](Rhs_t::value_type rhs_sub_element){
                                    return op_scalar_or_collection_with_collection<Op, true, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs);
                            });
                    }
                    }
                    else {
                    switch(source->execution_policy){
                        case thread_policy::unsequenced_exec:
                            return std::all_of(std::execution::unseq , lhs->begin(), lhs->end(),
                                [](Rhs_t::value_type rhs_sub_element){
                                    if (op_scalar_or_collection_with_collection<Op, false, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs)){
                                        return false;
                                    }
                            });
                        case thread_policy::unsequenced_parrallel_exec:
                            return std::all_of(std::execution::par_unseq , lhs->begin(), lhs->end(),
                                [](Rhs_t::value_type rhs_sub_element){
                                    if (op_scalar_or_collection_with_collection<Op, false, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs)){
                                        return false; 
                                    }
                            });
                    }
                    }

                    }

            template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
            requires{//the concept is weather the expression below works or not
            typename std::common_type_t
            <std::iterator_traits<Rhs_t::iterator>::iterator_category, std::input_iterator_tag>;
            }
                inline typename std::conditional<op_action_type == true, void, bool>  
                    op_scalar_with_collection(Lhs_t* lhs,const Nested_type_info rhs){
                    const auto& formated_rhs= 
                    *(static_cast<Rhs_t*>(rhs->ptr));
                    if constexpr (op_action_type == true) {
                        switch(source->execution_policy){
                            case thread_policy::unsequenced_exec:
                                std::for_each(std::execution::unseq, formated_rhs.begin(), formated_rhs.end(),
                                    [](const Rhs_t::value_type rhs_sub_element){
                                        return op_scalar_or_collection_with_collection<Op, true, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element);
                                    
                                });
                            case thread_policy::unsequenced_parrallel_exec:
                                std::for_each(std::execution::par_unseq, formated_rhs.begin(), formated_rhs.end(), Lhs_t{},
                                    [](const Rhs_t::value_type rhs_sub_element){
                                        return op_scalar_or_collection_with_collection<Op, true, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element);
                                    
                                });
                        }
                    }
                    else {
                        switch(source->execution_policy){
                            case thread_policy::unsequenced_exec:
                                return std::all_of(std::execution::unseq, rhs.begin(), rhs.end(),
                                    [](const Rhs_t::value_type rhs_sub_element){
                                        if (op_scalar_or_collection_with_collection<Op, false, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element)){
                                            return false;
                                        }
                                    
                                });
                            case thread_policy::unsequenced_parrallel_exec:
                                return std::all_of(std::execution::par_unseq, rhs.begin(), rhs.end(),
                                    [](const Rhs_t::value_type rhs_sub_element){
                                        if (op_scalar_or_collection_with_collection<Op, false, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element)){
                                            return false; 
                                        }
                                });
                        }
                    }
                }

                template<typename Op, bool op_action_type,typename Lhs_t, typename Rhs_t>
                inline inline typename std::conditional<op_action_type == true, void, bool>  
                all_action_on_ops_for_simple_ops_on_void_pointers_collections(const Polymoprhic_extensible_engine first_obj, const Polymoprhic_extensible_engine second_obj) {
                Lhs_t* formated_lhs= static_cast<Lhs_t*>(first_obj);
                switch(second_obj->tag){
                case Type_tag_for_input::array_nested_type_vector:
                    using Rhs_t= std::vector<Polymoprhic_extensible_engine>;
                    return op_scalar_with_collection<Op, op_action_type, Lhs_t, Rhs_t>(formated_lhs, Nested_type_info{
                        second_obj->execution_policy,
                        second_obj->ptr});
                    break;
                case Type_tag_for_input::array_nested_type_deque:
                    using Rhs_t= std::deque<Polymoprhic_extensible_engine>;
                    return op_scalar_with_collection<Op, op_action_type, Lhs_t, Rhs_t>(formated_lhs, Nested_type_info{
                        second_obj->execution_policy,
                        second_obj->ptr});
                    break;
                case Type_tag_for_input::array_nested_type_list:
                    using Rhs_t= std::list<Polymoprhic_extensible_engine>;
                    return op_scalar_with_collection<Op, op_action_type, Lhs_t, Rhs_t>(formated_lhs, Nested_type_info{
                        second_obj->execution_policy,
                        second_obj->ptr});
                case Type_tag_for_input::array_nested_type_forward_list:
                    using Rhs_t= std::forward_list<Polymoprhic_extensible_engine>;
                    return op_scalar_with_collection<Op, op_action_type, Lhs_t, Rhs_t>(formated_lhs, Nested_type_info{
                        second_obj->execution_policy,
                        second_obj->ptr});
                //Todo redis maps 
                default:
                    throw std::string{"Invalid Container Tag"};
                    break;
                }
                 //notice a pattern that what ever template is used, the first two arguments are the constant "op, op_action_type", while 
                 //the last two is the lhs_type(first hand) and rhs_type(second hand).
                 //the same exact pattern is consistent in the implementations of these templates
                 //pass lhs as pointer of lhs_t type in all functions except the entry functions that FLAAAT_JuMPEnTeRYGeNAraT0r itself uses.
                 //pass rhs as const reference of rhs type in all functions except the entry functions that FLAAAT_JuMPEnTeRYGeNAraT0r itself 
                 //uses.
                 //all_action_on_ops_for_simple_ops_on_void_pointers_collections's usage of op_scalar_with_collection differs from this in that 
                 //it passes a Nested_type_info (by value) and also the rhs_t type, in that case rhs_t specifies the type of what 
                 //the void pointer points to.
                 //all tags are resolved here or (in the case of nested types only) in all_action_on_ops_for_simple_ops_on_void_pointers_collections.
                 //In the implementations, only the types speak
            #define FLAAAT_JuMPEnTeRYGeNAraT0r(op, \
                            op_action_type,
                            only_tag_for_first_paremeter\
                            first_obj,\
                            second_obj,\
                             ) \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::string_tag_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::string>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::uintptr_tag_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, uintptr_t>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::intptr_tag_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, intptr_t>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, long double>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::eight_byte_double_tag_for_15_plus_operand_ops): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, double>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::eight_byte_double_tag): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, double>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::uintptr_tag): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, uintptr_t>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::string_tag): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::string>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::intptr_tag): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, intptr_t>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_string): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<std::string>>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_uintptr): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<uintptr_t>>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_intptr): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<intptr_t>>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_double): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<double>>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::vector_long_double_tag_implementation_defined_size): \
        return all_action_on_ops_for_simple_ops_on_void_pointers<op, op_action_type, only_arg_type_for_first_paremeter, std::vector<long double>>(first_obj, second_obj); \
    case produce_jump_index(only_tag_for_first_paremeter, Type_tag::nested_type_with_dynamic_container): \ 
        all_action_on_ops_for_simple_ops_on_void_pointers_collections<op, op_action_type, only_arg_type_for_first_paremeter, Nested_type_info>(first_obj, second_obj);



        


        


            
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
                        Nested_type_info underlying_obj= *(static_cast<Nested_type_info*>(source.ptr));
                        switch(underlying_obj->tag){
                            case Type_tag_for_input::array_nested_type_vector:
                                using Source_and_target_type= std::vector<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::vector_containing_types>(underlying_obj);
                                break;
                            case Type_tag_for_input::array_nested_type_deque:
                                using Source_and_target_type= std::deque<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::type_in_deque_tag>(underlying_obj);
                                break;
                            case Type_tag_for_input::array_nested_type_list:
                                using Source_and_target_type= std::list<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::type_in_list>(underlying_obj);
                            case Type_tag_for_input::array_nested_type_forward_list:
                                using Source_and_target_type= std::forward_list<Polymoprhic_extensible_engine>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::type_in_forward_list>(underlying_obj);
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
                static inline void*  copy_nested(Nested_type_info source){
                    underlying_container_specialization& formated_source= 
                    *(static_cast<underlying_container_specialization*>(source->ptr));
                    //NOTE: underlying_container_specialization is a container type.
                    underlying_container_specialization& destination_data= *(new underlying_container_specialization(formated_source.size()));
                    switch(source->execution_policy){
                    case thread_policy::unsequenced_exec:
                        std::copy(std::execution::unseq , formated_source.begin(), formated_source.end(), destination_data.begin(), 
                            [](value_type source_ptr){
                                return Polymoprhic_extensible_engine(source_ptr);
                            
                        });
                    case thread_policy::unsequenced_parrallel_exec:
                        std::copy(std::execution::par_unseq , formated_source.begin(), formated_source.end(), destination_data.begin(), 
                            [](value_type source_ptr){
                                return Polymoprhic_extensible_engine(source_ptr);
                            
                        });
                    }
                    return static_cast<void*>(new Nested_type_info{tag, source->execution_policy, static_cast<void*>(destination_data)}); 

                }

                template<typename Op, ternary_state op_action_type>
                inline typename std::conditional<op_action_type == true, void, bool>
                    void_op_generator(Polymoprhic_extensible_engine second_arg){
                    switch(produce_jump_index(tag, second_arg.tag)){
                        /* --- Full Outer Dispatch Table Dispatch for first ARG(also known as Lhs) (using macros); the code generated would be a flat map. The macro takes care of the second arg(also known as Rhs)--- */
                    
                        // [beginning(0 index) - 05): High-Operand Specialized
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, std::string, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, uintptr_t, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, intptr_t, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, long_double, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, Fixed_size_floats, *this, second_arg)
                        
                        // [05 - 11): Scalar Primitives
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, long_double, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, Fixed_size_floats, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, uintptr_t, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, std::string, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, intptr_t, *this, second_arg)
                        
                        // [11 - 12): Containers
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<std::string>, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<uintptr_t>, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<intptr_t>, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<double>, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, std::vector<long double>, *this, second_arg)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, Nested_type_info, *this, second_arg)
                        
                        default:
                            throw std::string{"Unimplemented type"};
                        
                        }    
                    }
                  template<typename Op, ternary_state op_action_type>
                inline typename std::conditional<op_action_type == true, void, bool>
                    void_op_generator(void* second_arg_ptr){
                        
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
                        auto* underlying_obj = static_cast<Nested_type_info*>(ptr);
                        
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








































































