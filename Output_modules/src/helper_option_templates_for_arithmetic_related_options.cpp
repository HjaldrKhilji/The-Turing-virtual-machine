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

                enum class Type_tag : uint8_t {
                    /* --- High-Operand Specialized Tags --- */
                    string_tag_for_15_plus_operand_ops          = 0,
                    uintptr_tag_for_15_plus_operand_ops         = 1,
                    intptr_tag_for_15_plus_operand_ops          = 2,
                    long_double_tag_implementation_defined_size_for_15_plus_operand_ops  = 3,
                    /* --- Scalar Primitive Types --- */
                    long_double_tag_implementation_defined_size,
                    uintptr_tag,
                    string_tag,
                    intptr_tag,
                    
                    /* --- Contiguous & Dynamic Containers --- */
                    vector_string,
                    vector_uintptr,
                    vector_intptr,
                    vector_long_double_tag_implementation_defined_size,
                    nested_type_with_dynamic_container,
                    predict,
                    user_defined_binary_code_ops,
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
                    linked,
                    
                    /* --- Interface, Events & Extensibility --- */
                    gui,
                    capture_event,
                    confirm_event,
                    other,
                    //monolothic resource (purely for physical resource_management!)
                    monolithic_buffer_resource_tag,
                    all_elements_size_uintptr_t_tag
                
                    // not all of them would be implemented right now, like it would be a step by step process, 
                    // but all of them will have a respective entry until they are implemented
                };
                      
                enum class Type_tag_for_input : uint8_t {
                    /* --- High-Operand Specialized Tags --- */
                    string_tag_for_15_plus_operand_ops          = 0,
                    uintptr_tag_for_15_plus_operand_ops         = 1,
                    intptr_tag_for_15_plus_operand_ops          = 2,
                    long_double_tag_implementation_defined_size_for_15_plus_operand_ops  = 3,
                    /* --- Scalar Primitive Types --- */
                    long_double_tag_implementation_defined_size,
                    uintptr_tag,
                    string_tag,
                    intptr_tag,
                    
                    /* --- Contiguous & Dynamic Containers --- */
                    vector_string,
                    vector_uintptr,
                    vector_intptr,
                    vector_long_double_tag_implementation_defined_size,
                    nested_type_with_dynamic_container,
                    predict,
                    user_defined_binary_code_ops,

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
                    linked,
                    
                    /* --- Interface, Events & Extensibility --- */
                    gui,
                    capture_event,
                    confirm_event,
                    other,
                    
                    /* --- Container Nesting (Gateway Tags) --- */
                    array_nested_type_vector,
                    array_nested_type_deque,
                    array_nested_type_list,
                    array_nested_type_forward_list,
                    array_nested_type_redis_map
            };
            constexpr inline uint8_t produce_jump_index(Type_tag type_x, Type_tag type_y){
                return (static_cast<uint8_t>(type)>>4)+type_y;
            }
           enum class Type_storage_facility: uint8_t{
                type_in_array_tag=0,
                type_in_vector_tag=1,
                type_in_deque_tag=2,
                type_in_map_tag=3,
                type_in_hash_map_tag,
                type_in_list,
                type_in_forward_list,
                newly_defined_temp_type_for_new_obj,
                newly_defined_type_for_new_obj,
                just_trying_to_define_a_new_type_without_making_any_objects
            };
            sturct Extented_type_info{
                Type_storage_facility tag;
                uintptr_t index;
            };
            enum monolothic_resource_index{
            monolithic_buffer_resource_index;
            all_elements_size_uintptr_t_index=1;
            };
            static constexpr auto indexes_to_skip = std::max(monolithic_buffer_resource_index, all_elements_size_uintptr_t_index);
            std::vector<std::vector<Type_tag>> vector_containing_types;
            std::deque<std::vector<Type_tag>> deque_containing_types;
            std::list<std::vector<Type_tag>> list_containing_types;
            std::forward_list<std::vector<Type_tag>> forward_list_containing_types;
            std::map<uintptr_t,std::vector<Type_tag>> map_containing_types;
            std::unordered_map<uintptr_t,std::vector<Type_tag>> hash_map_containing_types;
            std::array<std::vector<Type_tag>, 100> array_containing_types{{}};

            enum class thread_policy : uint8_t {
            unsequenced_exec,
            unsequenced_parrallel_exec
            }; //notice that all operations are unsequenced
            struct Nested_type_info{
                Type_tag_for_input tag;
                thread_policy execution_policy;
                void* ptr;
            };
            template<typename T>
            struct No_tag_template_type_info{
            using underlying_container= t;
            thread_policy execution_policy;
            T ptr;
            //Nested_type_info resolves to  No_tag_template_type_info
            //vectors of primitive types and strings are wrapped inside No_tag_template_type_info
            };
            namespace polymorphic_extensible_engine{
            namespace implementation_of_the_interface_used_by_macro{
            namespace scalar_to_scalar{
                template<typename T>
                concept Polymorphic_object = require(Lhs_t a){
                    {Lhs_t.ptr}->std::same_as<void>;
                    {Lhs_t.tag}->std::same_as<Type_tag>;
                };
                template<typename Op, bool op_action_type, absolute_base::Is_String_Or_Numeric Lhs_t,absolute_base::Is_String_Or_Numeric Rhs_t>
                    inline typename std::conditional<op_action_type == true, void, bool>
                    all_ops(Lhs_t* lhs,const Rhs_t& rhs) {
                        //Everything will naturally use this!
                        if constexpr (op_action_type == true) {
                            *lhs = Op{}(std::ref(*lhs), std::cref(rhs)); 
                        }
                        else {
                            return Op{}(std::ref(*Lhs_t), std::cref(rhs));;
                        }
                    }
                template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
                    inline typename std::conditional<op_action_type == true, void, bool>
                    all_ops(Lhs_t* lhs,const Rhs_t& rhs) {
                        op_generator(lhs, rhs)
                    }

    
                };
                 
    
                
                     
                template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
                inline typename std::conditional<op_action_type == true, void, bool>  
                    op_scalar_or_collection_with_collection(Lhs_t* lhs,const Rhs_t& rhs){
                        return all_ops<Op, op_action_type, Lhs_t, Rhs_t>(lhs, rhs);
                }
    
    
                
                template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
                requires{//the concept is weather the expression below works or not
                typename std::derived_from
                <std::iterator_traits<Lhs_t::underlying_container::iterator>::iterator_category, std::input_iterator_tag>;
                }
                inline typename std::conditional<op_action_type == true, void, bool>  
                    op_scalar_or_collection_with_collection(Lhs_t* lhs,const Rhs_t& rhs){
                        switch(lhs->execution_policy){
                            case thread_policy::unsequenced_exec:
                                std::for_each(std::execution::unseq , lhs->begin(), lhs->end(),
                                    [](const auto& lhs_sub_element){
                                         return all_ops<Op, op_action_type, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs);
                                });
                            case thread_policy::unsequenced_parrallel_exec:
                                std::for_each(std::execution::par_unseq , lhs->begin(), lhs->end(),
                                    [](const auto& lhs_sub_element){
                                        return all_ops<Op, op_action_type, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs);
                                });
                        }
                template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
                requires{//the concept is weather the expression below works or not
                typename std::derived_from
                <std::iterator_traits<Lhs_t::underlying_container::iterator>::iterator_category, std::random_access_iterator_tag>;
                }&&Polymorphic_object(Lhs_t::value_type)
                inline typename std::conditional<op_action_type == true, void, bool>  
                    op_scalar_or_collection_with_collection(Lhs_t* lhs,const Rhs_t& rhs){
                        switch(lhs->execution_policy){
                            case thread_policy::unsequenced_exec:
                                std::for_each(std::execution::unseq , lhs->begin()+indexes_to_skip, lhs->end(),
                                    [](const auto& lhs_sub_element){
                                         return all_ops<Op, op_action_type, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs);
                                });
                            case thread_policy::unsequenced_parrallel_exec:
                                std::for_each(std::execution::par_unseq , lhs->begin()+indexes_to_skip, lhs->end(),
                                    [](const auto& lhs_sub_element){
                                        return all_ops<Op, op_action_type, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs);
                                });
                        }
    
                        }
    
                template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
                require{
                    std::derived_from(Nested_type_info, Lhs_t); //requirement is 
                    //just to make clear that Lhs_t is Nested_type_info, while keeping the interface uniform 
                }
                inline typename std::conditional<op_action_type == true, void, bool> 
                     
                    op_scalar_or_collection_with_collection(Lhs_t* lhs,const Rhs_t& rhs){
                
                switch(lhs->tag){
                    case Type_tag_for_input::array_nested_type_vector:
                        using Lhs_t_forwarded= std::vector<Polymoprhic_extensible_engine>;
                        return op_scalar_or_collection_with_collection<Op, op_action_type>(No_tag_template_type_info<Lhs_t_forwarded>{
                            lhs->execution_policy,
                            static_cast<Lhs_t_forwarded>(lhs->ptr)},
                            rhs);
                        break;
                    case Type_tag_for_input::array_nested_type_deque:
                        using Rhs_t_forwarded= std::deque<Polymoprhic_extensible_engine>;
                        return op_scalar_or_collection_with_collection<Op, op_action_type>(No_tag_template_type_info<Lhs_t_forwarded>{
                            lhs->execution_policy,
                            static_cast<Lhs_t_forwarded>(lhs->ptr)},
                            rhs);
                        break;
                    case Type_tag_for_input::array_nested_type_list:
                        using Rhs_t_forwarded= std::list<Polymoprhic_extensible_engine>;
                        return op_scalar_or_collection_with_collection<Op, op_action_type>(No_tag_template_type_info<Lhs_t_forwarded>{
                            lhs->execution_policy,
                            static_cast<Lhs_t_forwarded>(lhs->ptr)},
                            rhs);
                    case Type_tag_for_input::array_nested_type_forward_list:
                        using Rhs_t_forwarded= std::forward_list<Polymoprhic_extensible_engine>;
                        return op_scalar_or_collection_with_collection<Op, op_action_type>(No_tag_template_type_info<Lhs_t_forwarded>{
                            lhs->execution_policy,
                            static_cast<Lhs_t_forwarded>(lhs->ptr)},
                            rhs);
                    //Todo redis maps 
                    default:
                        throw std::string{"Invalid Container Tag"};
                        break;
                    }
                        
                        }        
                };

                namespace interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro{
                
                template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
                requires{//the concept is weather the expression below works or not
                typename std::derived_from
                <std::iterator_traits<Rhs_t::underlying_container::iterator>::iterator_category, std::input_iterator_tag>;
                }
                    inline typename std::conditional<op_action_type == true, void, bool>  
                        op_potential_scalar_with_collection(Lhs_t* lhs,const Rhs_t& rhs){
                        auto& formated_rhs= *(rhs->ptr);
                            switch(rhs.execution_policy){
                                case thread_policy::unsequenced_exec:
                                    std::for_each(std::execution::unseq, formated_rhs->begin(), formated_rhs->end(),
                                        [](const auto& rhs_sub_element){
                                            return op_scalar_or_collection_with_collection<Op, op_action_type, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element);
                                    });
                                case thread_policy::unsequenced_parrallel_exec:
                                    std::for_each(std::execution::par_unseq, formated_rhs->begin(), formated_rhs->end(), Lhs_t{},
                                        [](const auto& rhs_sub_element){
                                            return op_scalar_or_collection_with_collection<Op, op_action_type, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element);
                                    });
                            }
                    }
                template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
                requires{//the concept is weather the expression below works or not
                typename std::derived_from
                <std::iterator_traits<Rhs_t::underlying_container::iterator>::iterator_category, std::random_access_iterator_tag>;
                }&&Polymorphic_object(Rhs_t::value_type)
                    inline typename std::conditional<op_action_type == true, void, bool>  
                        op_potential_scalar_with_collection(Lhs_t* lhs,const Rhs_t& rhs){
                        auto& formated_rhs= *(rhs->ptr);
                            switch(rhs.execution_policy){
                                case thread_policy::unsequenced_exec:
                                    std::for_each(std::execution::unseq, formated_rhs->begin()+indexes_to_skip, formated_rhs->end(),
                                        [](const auto& rhs_sub_element){
                                            return op_scalar_or_collection_with_collection<Op, op_action_type, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element);
                                    });
                                case thread_policy::unsequenced_parrallel_exec:
                                    std::for_each(std::execution::par_unseq, formated_rhs->begin()+indexes_to_skip, formated_rhs->end(), Lhs_t{},
                                        [](const auto& rhs_sub_element){
                                            return op_scalar_or_collection_with_collection<Op, op_action_type, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element);
                                    });
                            }
                    }
                };    



                namespace interface_used_by_macro{


                    template<typename Op, bool op_action_type,typename Lhs_t, typename Rhs_t>
                    inline inline typename std::conditional<op_action_type == true, void, bool>  
                     require{

                     }
                    interface_of_all_operations_on_potential_scaler_with_potential_scalar(const Polymoprhic_extensible_engine first_obj, const Polymoprhic_extensible_engine second_obj) {
                    Lhs_t* formated_lhs= static_cast<Lhs_t*>(first_obj->ptr);
                    Rhs_t* formated_rhs= static_cast<Rhs_t*>(second_obj->ptr);
                    implementation_of_the_interface_used_by_macro::op_potential_scalar_with_collection<Op, op_action_type>(formated_lhs, formated_rhs);
                    }
                    template<typename Op, bool op_action_type,typename Lhs_t, typename Rhs_t>
                    inline inline typename std::conditional<op_action_type == true, void, bool>  
                     require{

                     }
                    interface_of_all_ops_scalar_to_scalar(const Polymoprhic_extensible_engine first_obj, const Polymoprhic_extensible_engine second_obj) {
                    Lhs_t* formated_lhs= static_cast<Lhs_t*>(first_obj->ptr);
                    Rhs_t* formated_rhs= static_cast<Rhs_t*>(second_obj->ptr);
                    implementation_of_the_interface_used_by_macro::all_ops<Op, op_action_type>(formated_lhs, formated_rhs);
                    }
                    template<typename Op, bool op_action_type,typename Lhs_t, typename Rhs_t>
                    inline inline typename std::conditional<op_action_type == true, void, bool>  
                     require{
                         std::derived_from(Nested_type_info, Rhs_t); //requirement is 
                         //just to make clear that Rhs_t is Nested_type_info, while keeping the interface uniform 
                     }
                    interface_of_all_operations_on_potential_scaler_with_collections_of_polymorphic_engine_objects(const Polymoprhic_extensible_engine first_obj, const Polymoprhic_extensible_engine second_obj) {
                    Lhs_t* formated_lhs= static_cast<Lhs_t*>(first_obj->ptr);
                    Rhs_t* formated_rhs= static_cast<Rhs_t*>(second_obj->ptr);
                    switch(second_obj->tag){
                    case Type_tag_for_input::array_nested_type_vector:
                        using Rhs_t_forwarded= std::vector<Polymoprhic_extensible_engine>;
                        return implementation_of_the_interface_used_by_macro::op_potential_scalar_with_collection<Op, op_action_type>(formated_lhs, No_tag_template_type_info<Rhs_t_forwarded>{
                            second_obj->execution_policy,
                            static_cast<Rhs_t_forwarded>(second_obj->ptr)});
                        break;
                    case Type_tag_for_input::array_nested_type_deque:
                        using Rhs_t_forwarded= std::deque<Polymoprhic_extensible_engine>;
                        return implementation_of_the_interface_used_by_macro::op_potential_scalar_with_collection<Op, op_action_type>(formated_lhs, No_tag_nested_type_info<Rhs_t_forwarded>{
                            second_obj->execution_policy,
                            static_cast<Rhs_t_forwarded>(second_obj->ptr)});
                        break;
                    case Type_tag_for_input::array_nested_type_list:
                        using Rhs_t_forwarded= std::list<Polymoprhic_extensible_engine>;
                        return implementation_of_the_interface_used_by_macro::op_potential_scalar_with_collection<Op, op_action_type>(formated_lhs, No_tag_nested_type_info<Rhs_t_forwarded>{
                            second_obj->execution_policy,
                            static_cast<Rhs_t_forwarded>(second_obj->ptr)});
                    case Type_tag_for_input::array_nested_type_forward_list:
                        using Rhs_t_forwarded= std::forward_list<Polymoprhic_extensible_engine>;
                        return implementation_of_the_interface_used_by_macro::op_potential_scalar_with_collection<Op, op_action_type>(formated_lhs, No_tag_nested_type_info<Rhs_t_forwarded>{
                            second_obj->execution_policy,
                            static_cast<Rhs_t_forwarded>(second_obj->ptr)});
                    //Todo redis maps 
                    default:
                        throw std::string{"Invalid Container Tag"};
                        break;
                    }
                    }
                };


                // note: the macro is pure text substituion, so dont expect it to do anything else!
                 //notice a pattern that what ever template is used, the first two arguments are the constant "op, op_action_type", while 
                 //the last two is the lhs_type(first hand) and rhs_type(second hand).
                 //the same exact pattern is consistent in the implementations of these templates
                 //pass lhs as pointer of lhs_t type in all functions except the entry functions that FLAAAT_JuMPEnTeRYGeNAraT0r itself uses.
                 //pass rhs as const reference of rhs type in all functions except the entry functions that FLAAAT_JuMPEnTeRYGeNAraT0r itself 
                 //uses.
                 //all tags are resolved in the first call from the macro. 
                 //In the implementations(functions not directly called by the macros), only the types speak.



        #define FLAAAT_JuMPEnTeRYGeNAraT0r(op, \
        op_action_type,\
        only_arg_type_for_first_paremeter,\
        first_obj,\
        second_obj,\
        tag_for_switching\
        ) \
    case produce_jump_index(tag_for_switching, Type_tag::string_tag_for_15_plus_operand_ops): \
        return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, std::string>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::uintptr_tag_for_15_plus_operand_ops): \
        return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, uintptr_t>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::intptr_tag_for_15_plus_operand_ops): \
        return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, intptr_t>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops): \
        return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, long double>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::long_double_tag_implementation_defined_size): \
        return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, long double>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::uintptr_tag): \
        return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, uintptr_t>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::string_tag): \
        return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, std::string>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::intptr_tag): \
        return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, intptr_t>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::vector_string): \
        return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, No_tag_nested_type_info<std::vector<std::string>>>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::vector_uintptr): \
        return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, No_tag_nested_type_info<std::vector<uintptr_t>>>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::vector_intptr): \
        return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, No_tag_nested_type_info<std::vector<intptr_t>>>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::vector_long_double_tag_implementation_defined_size): \
        return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, No_tag_nested_type_info<std::vector<long double>>>(first_obj, second_obj); \
    case produce_jump_index(tag_for_switching, Type_tag::nested_type_with_dynamic_container): \ 
        return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_collections_of_polymorphic_engine_objects<op, op_action_type, only_arg_type_for_first_paremeter, Nested_type_info>(first_obj, second_obj);

        template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t, Type_tag tag_for_switching>
        inline typename std::conditional<op_action_type == true, void, bool> 
        runtime_branching_using_only_second_arg(first_non_polymorphic_obj, second_obj){
        switch(second_obj->tag){
            case Type_tag::string_tag_for_15_plus_operand_ops: 
                return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,only_arg_type_for_first_paremeter,std::string>(first_non_polymorphic_obj, second_obj); 
            case Type_tag::uintptr_tag_for_15_plus_operand_ops: 
                return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,only_arg_type_for_first_paremeter,uintptr_t>(first_non_polymorphic_obj, second_obj); 
            case Type_tag::intptr_tag_for_15_plus_operand_ops: 
                return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,only_arg_type_for_first_paremeter,intptr_t>(first_non_polymorphic_obj, second_obj); 
            case Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops: 
                return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,only_arg_type_for_first_paremeter,long double>(first_non_polymorphic_obj, second_obj); 
            case Type_tag::long_double_tag_implementation_defined_size: 
                return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,only_arg_type_for_first_paremeter,long double>(first_non_polymorphic_obj, second_obj); 
            case Type_tag::uintptr_tag: 
                return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,only_arg_type_for_first_paremeter,uintptr_t>(first_non_polymorphic_obj, second_obj); 
            case Type_tag::string_tag: 
                return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,only_arg_type_for_first_paremeter,std::string>(first_non_polymorphic_obj, second_obj); 
            case Type_tag::intptr_tag: 
                return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,only_arg_type_for_first_paremeter,intptr_t>(first_non_polymorphic_obj, second_obj); 
            case Type_tag::vector_string: 
                return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, No_tag_nested_type_info<std::vector<std::string>>>(first_obj, second_obj); 
            case Type_tag::vector_uintptr: 
                return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, No_tag_nested_type_info<std::vector<uintptr_t>>>(first_obj, second_obj); 
            case Type_tag::vector_intptr: 
                return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, No_tag_nested_type_info<std::vector<intptr_t>>>(first_obj, second_obj); 
            case Type_tag::vector_long_double_tag_implementation_defined_size: 
                return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, only_arg_type_for_first_paremeter, No_tag_nested_type_info<std::vector<long double>>>(first_obj, second_obj); 
            case Type_tag::nested_type_with_dynamic_container: 
                return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_collections_of_polymorphic_engine_objects<op, op_action_type, only_arg_type_for_first_paremeter, Nested_type_info>(first_obj, second_obj);
        }
        }
        
        template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t, Type_tag tag_for_switching>
        inline typename std::conditional<op_action_type == true, void, bool> 
        runtime_branching_using_only_first_arg(first_non_polymorphic_obj, second_obj){
            switch(second_obj->tag){
                case Type_tag::string_tag_for_15_plus_operand_ops: 
                    return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,std::string, only_arg_type_for_second_paremeter>(first_non_polymorphic_obj, second_obj); 
                case Type_tag::uintptr_tag_for_15_plus_operand_ops: 
                    return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,uintptr_t, only_arg_type_for_second_paremeter>(first_non_polymorphic_obj, second_obj); 
                case Type_tag::intptr_tag_for_15_plus_operand_ops: 
                    return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,intptr_t, only_arg_type_for_second_paremeter>(first_non_polymorphic_obj, second_obj); 
                case Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops: 
                    return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,long double, only_arg_type_for_second_paremeter>(first_non_polymorphic_obj, second_obj); 
                case Type_tag::long_double_tag_implementation_defined_size: 
                    return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,long double, only_arg_type_for_second_paremeter>(first_non_polymorphic_obj, second_obj); 
                case Type_tag::uintptr_tag: 
                    return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,uintptr_t, only_arg_type_for_second_paremeter>(first_non_polymorphic_obj, second_obj); 
                case Type_tag::string_tag: 
                    return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,std::string, only_arg_type_for_second_paremeter>(first_non_polymorphic_obj, second_obj); 
                case Type_tag::intptr_tag: 
                    return interface_used_by_macro::interface_of_all_ops_scalar_to_scalar<op, op_action_type,intptr_t, only_arg_type_for_second_paremeter>(first_non_polymorphic_obj, second_obj); 
                case Type_tag::vector_string: 
                    return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, No_tag_nested_type_info<std::vector<std::string>, only_arg_type_for_second_paremeter>>(first_obj, second_obj); 
                case Type_tag::vector_uintptr: 
                    return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, No_tag_nested_type_info<std::vector<uintptr_t>>,  only_arg_type_for_second_paremeter>(first_obj, second_obj); 
                case Type_tag::vector_intptr: 
                    return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, No_tag_nested_type_info<std::vector<intptr_t>>,   only_arg_type_for_second_paremeter>(first_obj, second_obj); 
                case Type_tag::vector_long_double_tag_implementation_defined_size:
                    return interface_used_by_macro_but_also_implementation_of_some_interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_potential_scalar<op, op_action_type, No_tag_nested_type_info<std::vector<long double>>,only_arg_type_for_second_paremeter>(first_obj, second_obj); 
                case Type_tag::nested_type_with_dynamic_container: 
                    return interface_used_by_macro::interface_of_all_operations_on_potential_scaler_with_collections_of_polymorphic_engine_objects<op, op_action_type, Nested_type_info, only_arg_type_for_second_paremeter>(first_obj, second_obj);
            }
        }

        



            struct Polymoprhic_extensible_engine{
            //least confusing cpp code in the world, hahahaha.
            Type_tag tag;
            void *ptr;
            

            constexpr Polymoprhic_extensible_engine(Type_tag tag_of_type_to_construct_from,void* source):
            tag{tag_of_type_to_construct_from}, ptr{source}{}


            template<typename T, Type_tag_for_input tag>
            constexpr Polymoprhic_extensible_engine(T* source):Polymoprhic_extensible_engine{
            Polymoprhic_extensible_engine{tag, source->ptr}
            } {}

            inline Polymoprhic_extensible_engine operator=(Polymoprhic_extensible_engine source){
            ~Polymoprhic_extensible_engine();
            *this= Polymoprhic_extensible_engine{source};
            }
            inline Polymoprhic_extensible_engine operator=(Polymoprhic_extensible_engine&& source){
            ptr= source.ptr;
            tag= source.tag;         
            }
            template<typename Underlying_container_specialization, Type_tag_for_input tag>
            requires{//the concept is weather the expression below works or not
            typename std::derived_from
                <std::iterator_traits<Underlying_container_specialization::underlying_container::iterator>::iterator_category, std::input_iterator_tag>;
            }
                static inline void*  copy_nested(Nested_type_info source){
                    underlying_container_specialization_and_thread_execution_policy& formated_source= 
                    *(static_cast<underlying_container_specialization_and_thread_execution_policy*>(source->ptr));
                    //NOTE: underlying_container_specialization is a container type.
                    underlying_container_specialization_and_thread_execution_policy& destination_data= *(new underlying_container_specialization_and_thread_execution_policy(source->execution_policy, formated_source.size()));
                    switch(source->execution_policy){
                    case thread_policy::unsequenced_exec:
                        std::copy(std::execution::unseq , formated_source.ptr.begin(), formated_source.ptr.end(), destination_data.ptr.begin(), 
                            [](const Polymoprhic_extensible_engine source_ptr){
                                return Polymoprhic_extensible_engine(source_ptr);
                            
                        });
                    case thread_policy::unsequenced_parrallel_exec:
                        std::copy(std::execution::par_unseq , formated_source.ptr.begin(), formated_source.ptr.end(), destination_data.ptr.begin(), 
                            [](const Polymoprhic_extensible_engine source_ptr){
                                return Polymoprhic_extensible_engine(source_ptr);
                            
                        });
                    }
                    return static_cast<void*>(new Nested_type_info{tag, source->execution_policy, static_cast<void*>(&destination_data)}); 

                }

            template<typename Underlying_container_specialization, Type_tag_for_input tag>
            requires{//the concept is weather the expression below works or not
            typename std::derived_from
                <std::iterator_traits<Underlying_container_specialization::underlying_container::iterator>::iterator_category, std::random_access_iterator_tag>;
            }
                static inline void*  copy_nested(Nested_type_info source){

                    underlying_container_specialization_and_thread_execution_policy& formated_source= 
                    *(static_cast<underlying_container_specialization_and_thread_execution_policy*>(source->ptr));
                    //NOTE: underlying_container_specialization is a container type.
                    size_t formated_size= *(static_cast<uintptr_t*>(formated_source[monolithic_buffer_resource_index].ptr));
                    using memory_region=std::pmr::monotonic_buffer_resource::monotonic_buffer_resource;
                    memory_region* buffer= new memory_region(formated_size);
                    std::pmr::polymorphic_allocator<std::byte> allocator_used{buffer};
                    underlying_container_specialization& destination_data= *(allocator_used.new_object<underlying_container_specialization_and_thread_execution_policy>(source->execution_policy,formated_source.size()));
                    destination_data[monolithic_buffer_resource_index] = {monolithic_buffer_resource_tag, static_cast<void*>(buffer)};
                    destination_data[all_elements_size_uintptr_t_index]= {all_elements_size_uintptr_t_tag,static_cast<void*>(allocator_used.new_object<size_t>(formated_size))};
                    switch(source->execution_policy){
                    case thread_policy::unsequenced_exec:
                        std::copy(std::execution::unseq , formated_source.ptr.begin()+indexes_to_skip, formated_source.ptr.end(), destination_data.ptr.begin()+indexes_to_skip, 
                            [](const Polymoprhic_extensible_engine source_ptr){
                                return Polymoprhic_extensible_engine(source_ptr, allocator_used);
                        });
                    case thread_policy::unsequenced_parrallel_exec:
                        std::copy(std::execution::par_unseq , formated_source.ptr.begin()+indexes_to_skip, formated_source.ptr.end(), destination_data.ptr.begin()+indexes_to_skip, 
                            [](const Polymoprhic_extensible_engine source_ptr){
                                return Polymoprhic_extensible_engine(source_ptr, allocator_used);
                        });
                    }
                    return static_cast<void*>(new Nested_type_info{tag, source->execution_policy, static_cast<void*>(&destination_data)}); 

                }
            inline Polymoprhic_extensible_engine(Polymoprhic_extensible_engine source){
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
                    /* --- Scalar Primitive Types --- */
                    case Type_tag::long_double_tag_implementation_defined_size: {
                        using Source_and_target_type = double;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::long_double_tag_implementation_defined_size;
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
                        using Source_and_target_type = No_tag_template_type_info<std::vector<std::string>>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::vector_string;
                        break;
                    }
                    case Type_tag::vector_uintptr: {
                        using Source_and_target_type = No_tag_template_type_info<std::vector<uintptr_t>>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::vector_uintptr;
                        break;
                    }
                    case Type_tag::vector_intptr: {
                        using Source_and_target_type = No_tag_template_type_info<std::vector<intptr_t>>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::vector_intptr;
                        break;
                    }
                    case Type_tag::vector_long_double_tag_implementation_defined_size: {
                        using Source_and_target_type = No_tag_template_type_info<std::vector<long double>>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(new Source_and_target_type{source_formatted});
                        tag = Type_tag::vector_long_double_tag_implementation_defined_size;
                        break;
                    }
                    case Type_tag::nested_type_with_dynamic_container:       
                        Nested_type_info underlying_obj= *(static_cast<Nested_type_info*>(source.ptr));
                        switch(underlying_obj->tag){
                            case Type_tag_for_input::array_nested_type_vector:{
                                using Source_and_target_type= No_tag_template_type_info<std::vector<Polymoprhic_extensible_engine>>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::vector_containing_types>(underlying_obj);
                                break;}
                            case Type_tag_for_input::array_nested_type_deque:{
                                using Source_and_target_type= No_tag_template_type_info<std::deque<Polymoprhic_extensible_engine>>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::type_in_deque_tag>(underlying_obj);
                                break;}
                            case Type_tag_for_input::array_nested_type_list:{
                                using Source_and_target_type= No_tag_template_type_info<std::list<Polymoprhic_extensible_engine>>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::type_in_list>(underlying_obj);
                                break;
                            }
                            case Type_tag_for_input::array_nested_type_forward_list:{
                                using Source_and_target_type= No_tag_template_type_info<std::forward_list<Polymoprhic_extensible_engine>>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::type_in_forward_list>(underlying_obj);
                                break;
                            }
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
            inline Polymoprhic_extensible_engine
            (Polymoprhic_extensible_engine source, std::pmr::polymorphic_allocator<std::byte> allocator_used){
               switch(source.tag){
                   /* --- High-Operand Specialized Tags --- */
                    case Type_tag::string_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = std::string;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::string_tag_for_15_plus_operand_ops;
                        break;
                    }
                    case Type_tag::uintptr_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = uintptr_t;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::uintptr_tag_for_15_plus_operand_ops;
                        break;
                    }
                    case Type_tag::intptr_tag_for_15_plus_operand_ops: {
                        using Source_and_target_type = intptr_t;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::intptr_tag_for_15_plus_operand_ops;
                        break;
                    }
                    case Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops: {
                        using Source_and_target_type = long double;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops;
                        break;
                    }
                    /* --- Scalar Primitive Types --- */
                    case Type_tag::long_double_tag_implementation_defined_size: {
                        using Source_and_target_type = double;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::long_double_tag_implementation_defined_size;
                        break;
                    }
                    case Type_tag::uintptr_tag: {
                        using Source_and_target_type = uintptr_t;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::uintptr_tag;
                        break;
                    }
                    case Type_tag::string_tag: {
                        using Source_and_target_type = std::string;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::string_tag;
                        break;
                    }
                    case Type_tag::intptr_tag: {
                        using Source_and_target_type = intptr_t;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::intptr_tag;
                        break;
                    }
                
                    /* --- Contiguous & Dynamic Containers --- */
                    case Type_tag::vector_string: {
                        using Source_and_target_type = No_tag_template_type_info<std::vector<std::string>>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::vector_string;
                        break;
                    }
                    case Type_tag::vector_uintptr: {
                        using Source_and_target_type = No_tag_template_type_info<std::vector<uintptr_t>>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::vector_uintptr;
                        break;
                    }
                    case Type_tag::vector_intptr: {
                        using Source_and_target_type = No_tag_template_type_info<std::vector<intptr_t>>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::vector_intptr;
                        break;
                    }
                    case Type_tag::vector_long_double_tag_implementation_defined_size: {
                        using Source_and_target_type = No_tag_template_type_info<std::vector<long double>>;
                        auto& source_formatted = *(static_cast<Source_and_target_type*>(source.ptr));
                        ptr = static_cast<void*>(allocator_used.new_object<Source_and_target_type>(source_formatted));
                        tag = Type_tag::vector_long_double_tag_implementation_defined_size;
                        break;
                    }
                    case Type_tag::nested_type_with_dynamic_container:       
                        Nested_type_info underlying_obj= *(static_cast<Nested_type_info*>(source.ptr));
                        switch(underlying_obj->tag){
                            case Type_tag_for_input::array_nested_type_vector:{
                                using Source_and_target_type= No_tag_template_type_info<std::vector<Polymoprhic_extensible_engine>>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::vector_containing_types>(underlying_obj);
                                break;}
                            case Type_tag_for_input::array_nested_type_deque:{
                                using Source_and_target_type= No_tag_template_type_info<std::deque<Polymoprhic_extensible_engine>>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::type_in_deque_tag>(underlying_obj);
                                break;}
                            case Type_tag_for_input::array_nested_type_list:{
                                using Source_and_target_type= No_tag_template_type_info<std::list<Polymoprhic_extensible_engine>>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::type_in_list>(underlying_obj);
                                break;}
                            case Type_tag_for_input::array_nested_type_forward_list:{
                                using Source_and_target_type= No_tag_template_type_info<std::forward_list<Polymoprhic_extensible_engine>>;
                                tag= Type_tag::nested_type_with_dynamic_container;
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::type_in_forward_list>(underlying_obj);
                                break;}
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
            typename std::derived_from
                <std::iterator_traits<Underlying_container_specialization::underlying_container::iterator>::iterator_category, std::input_iterator_tag>;
            }
                static inline void* make_nested(const std::string& string_to_read_from, std::string:size_type* pos,Type_tag tag_arg){
                    underlying_container_specialization_and_thread_execution_policy& formated_source= 
                    *(static_cast<underlying_container_specialization_and_thread_execution_policy*>(source->ptr));
                    //NOTE: underlying_container_specialization is a container type.
                    underlying_container_specialization_and_thread_execution_policy& destination_data= *(new underlying_container_specialization_and_thread_execution_policy(source->execution_policy, formated_source.size()));
                    switch(source->execution_policy){
                    case thread_policy::unsequenced_exec:
                        std::generate(std::execution::unseq , formated_source.ptr.begin(), formated_source.ptr.end(), 
                            [](const Polymoprhic_extensible_engine source_ptr){
                                return Polymoprhic_extensible_engine{string_to_read_from, pos, tag_arg};
                            
                        });
                    case thread_policy::unsequenced_parrallel_exec:
                        std::generate(std::execution::par_unseq , formated_source.ptr.begin(), formated_source.ptr.end(), 
                            [](const Polymoprhic_extensible_engine source_ptr){
                                return Polymoprhic_extensible_engine{string_to_read_from, pos, tag_arg};
                            
                        });
                    }
                    return static_cast<void*>(new Nested_type_info{tag, source->execution_policy, static_cast<void*>(destination_data)}); 

                }

            template<typename Underlying_container_specialization, Type_tag_for_input tag>
            requires{//the concept is weather the expression below works or not
            typename std::derived_from
                <std::iterator_traits<Underlying_container_specialization::underlying_container::iterator>::iterator_category, std::random_access_iterator_tag>;
            }
                static inline void*  make_nested(const std::string& string_to_read_from, std::string:size_type* pos,Type_tag tag_arg){
                    size_t size_to_reserve_for_elements= read_from_string<size_t>(string_to_read_from, pos);
                    size_t size_to_reserve_for_container= read_from_string<size_t>(string_to_read_from, pos);
                    size_t final_size= size_to_reserve_for_elements+size_to_reserve_for_container;
                    using memory_region=std::pmr::monotonic_buffer_resource::monotonic_buffer_resource;
                    memory_region* buffer= new memory_region(final_size);
                    std::pmr::polymorphic_allocator<std::byte> allocator_used{buffer};
                    underlying_container_specialization& underlying_data= *(allocator_used.new_object<underlying_container_specialization_and_thread_execution_policy>(source->execution_policy,formated_source.size()));
                    underlying_data[monolithic_buffer_resource_index] = {monolithic_buffer_resource_tag, static_cast<void*>(buffer)};
                    underlying_data[all_elements_size_uintptr_t_index]= {all_elements_size_uintptr_t_tag,static_cast<void*>(allocator_used.new_object<size_t>(final_size))};
                    switch(source->execution_policy){
                    case thread_policy::unsequenced_exec:
                        std::generate(std::execution::unseq , underlying_data.ptr.begin(), underlying_data.ptr.end(), 
                            [&string_to_read_from, &pos](){
                                return Polymoprhic_extensible_engine{string_to_read_from, pos,static_cast<Type_tag_for_input>(read_from_string<uint8_t>(string_to_read_from, pos_size))};
                        });
                    case thread_policy::unsequenced_parrallel_exec:
                        std::generate(std::execution::par_unseq , underlying_data.ptr.begin(), underlying_data.ptr.end(), 
                            [&string_to_read_from, &pos](){
                                return Polymoprhic_extensible_engine{string_to_read_from, pos,static_cast<Type_tag_for_input>(read_from_string<uint8_t>(string_to_read_from, pos_size))};
                        });
                    }
                    return static_cast<void*>(new Nested_type_info{
                                static_cast<Type_tag_for_input>(read_from_string<uint8_t>(string_to_read_from, pos_size)),
                                static_cast<thread_policy>(read_from_string<uint8_t>(string_to_read_from, pos_size)),
                                static_cast<void*>(&underlying_data);                                
                            }); 

                }
            inline  Polymoprhic_extensible_engine
            (const std::string& string_to_read_from, std::string:size_type* pos_size,Type_tag tag_arg){
                switch(tag_arg){
                    //to be completed
                    case Type_tag::string_tag_for_15_plus_operand_ops: 
                        {
                            using underlying_type_of_ptr= std::string;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }
                    case Type_tag::uintptr_tag_for_15_plus_operand_ops: 
                        {
                            using underlying_type_of_ptr= uintptr_t;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));                            tag= tag_arg;
                        }
                    case Type_tag::intptr_tag_for_15_plus_operand_ops: 
                        {
                            using underlying_type_of_ptr= intptr_t;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops: 
                        {
                            using underlying_type_of_ptr= long double;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::long_double_tag_implementation_defined_size: 
                        {
                            using underlying_type_of_ptr= long double;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::uintptr_tag: 
                        {
                            using underlying_type_of_ptr= uintptr_t;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::string_tag: 
                        {
                            using underlying_type_of_ptr= std::string;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::intptr_tag: 
                        {
                            using underlying_type_of_ptr= uintptr_t;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::vector_string: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<std::string>>;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::vector_uintptr: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<uintptr_t>>;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::vector_intptr: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<intptr_t>>;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                                    
                    case Type_tag::vector_long_double_tag_implementation_defined_size: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<long double>>;
                            ptr= static_cast<void*>
                                (new underlying_type_of_ptr(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                                 
                    case Type_tag::nested_type_with_dynamic_container: 
                        {
                            Type_tag_for_input underlying_nested_type_tag= static_cast<Type_tag_for_input>(read_from_string<uint8_t>(string_to_read_from, pos_size));
                            switch(underlying_nested_type_tag){
                                case Type_tag_for_input::array_nested_type_vector:{
                                    using Source_and_target_type= No_tag_template_type_info<std::vector<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::vector_containing_types>(underlying_obj);
                                    break;
                                    }
                                case Type_tag_for_input::array_nested_type_deque:{
                                    using Source_and_target_type= No_tag_template_type_info<std::deque<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::type_in_deque_tag>(underlying_obj);
                                    break;}
                                case Type_tag_for_input::array_nested_type_list:{
                                    using Source_and_target_type= No_tag_template_type_info<std::list<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::type_in_list>(underlying_obj);
                                    break;}
                                case Type_tag_for_input::array_nested_type_forward_list:{
                                    using Source_and_target_type= No_tag_template_type_info<std::forward_list<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::type_in_forward_list>(underlying_obj);
                                    break;}
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
            }


            template<typename Underlying_container_specialization>
            require{
            typename std::derived_from
                <std::iterator_traits<Underlying_container_specialization::underlying_container::iterator>::iterator_category, std::random_access_iterator_tag>;
            }
            inline void destruct_sequence_from_the_globally_specified_indexes_to_skip_variable(const Underlying_container_specialization& sequence_with_policy){
                const auto* container= sequence_with_policy.ptr;
                switch(sequence_with_policy->execution_policy){
                    case thread_policy::unsequenced_exec:
                        std::for_each(std::execution::unseq, container->begin()+indexes_to_skip, container->end(), 
                        [](const Polymoprhic_extensible_engine source_ptr){
                            source_ptr.~Polymoprhic_extensible_engine();
                        });
                    case thread_policy::unsequenced_parrallel_exec:
                        std::for_each(std::execution::par_unseq, container->begin()+indexes_to_skip, container->end(), 
                        [](const Polymoprhic_extensible_engine source_ptr){
                            source_ptr.~Polymoprhic_extensible_engine();
                        });
            }
    

            inline ~Polymoprhic_extensible_engine(){
                switch(tag) {
                    /* --- [ 00 - 05 ) High-Operand Specialized Tags (DESTRUCTIVE) --- */
                    case Type_tag::string_tag_for_15_plus_operand_ops: {
                        using Underlying_t = std::string;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case Type_tag::uintptr_tag_for_15_plus_operand_ops: {
                        using Underlying_t = uintptr_t;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case Type_tag::intptr_tag_for_15_plus_operand_ops: {
                        using Underlying_t = intptr_t;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops: {
                        using Underlying_t = long double;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }

                    /* --- [ 06 - 09 ) Scalar Primitive Types (DESTRUCTIVE) --- */
                    case Type_tag::long_double_tag_implementation_defined_size: {
                        using Underlying_t = long double;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case Type_tag::uintptr_tag: {
                        using Underlying_t = uintptr_t;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case Type_tag::string_tag: {
                        using Underlying_t = std::string;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case Type_tag::intptr_tag: {
                        using Underlying_t = intptr_t;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }

                    /* --- [ 09 - 13 ) Contiguous & Dynamic Containers (DESTRUCTIVE) --- */
                    case Type_tag::vector_string: {
                        using Underlying_t = No_tag_template_type_info<std::vector<std::string>>;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case Type_tag::vector_uintptr: {
                        using Underlying_t = No_tag_template_type_info<std::vector<uintptr_t>>;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case Type_tag::vector_intptr: {
                        using Underlying_t = No_tag_template_type_info<std::vector<intptr_t>>;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case Type_tag::vector_long_double_tag_implementation_defined_size: {
                        using Underlying_t = No_tag_template_type_info<std::vector<long double>>;
                        delete (static_cast<Underlying_t*>(ptr));
                        break;
                    }
                    case monolithic_buffer_resource_tag:
                        using Underlying_t = std::pmr::monotonic_buffer_resource::monotonic_buffer_resource;
                        delete (static_cast<Underlying_t*>(ptr));
                    /* --- [ 13 - 14 ) Nested Types (DESTRUCTIVE) --- */
                    case Type_tag::nested_type_with_dynamic_container: {
                        auto* underlying_obj = static_cast<Nested_type_info*>(ptr);
                        //all of the code below relies on recursive destructor calls
                        switch(underlying_obj->tag) {
                            case Type_tag_for_input::vector_containing_types: {
                                using underlying_container_specialization_and_thread_execution_policy = No_tag_template_type_info<std::vector<Polymoprhic_extensible_engine>>;
                                const underlying_container_specialization_and_thread_execution_policy& sequence_with_policy = 
                                *(static_cast<underlying_container_specialization_and_thread_execution_policy*>(underlying_obj->ptr));
                                destruct_sequence_from_the_globally_specified_indexes_to_skip_variable(sequence_with_policy);
                                ~((sequence_with_policy->ptr)[monolithic_buffer_resource_index])();
                                break;
                            }
                            case Type_tag_for_input::type_in_deque_tag: {
                                using underlying_container_specialization_and_thread_execution_policy = No_tag_template_type_info<std::deque<Polymoprhic_extensible_engine>>;
                                const underlying_container_specialization_and_thread_execution_policy& sequence_with_policy = 
                                *(static_cast<underlying_container_specialization_and_thread_execution_policy*>(underlying_obj->ptr));
                                destruct_sequence_from_the_globally_specified_indexes_to_skip_variable(sequence_with_policy);
                                ~((sequence_with_policy->ptr)[monolithic_buffer_resource_index])();                                break;
                            }
                            case Type_tag_for_input::type_in_list: {
                                using underlying_container_specialization_and_thread_execution_policy = No_tag_template_type_info<std::list<Polymoprhic_extensible_engine>>;
                                delete (static_cast<underlying_container_specialization_and_thread_execution_policy*>(underlying_obj->ptr));
                                break;
                            }
                            case Type_tag_for_input::type_in_forward_list: {
                                using underlying_container_specialization_and_thread_execution_policy = No_tag_template_type_info<std::forward_list<Polymoprhic_extensible_engine>>;
                                delete (static_cast<underlying_container_specialization_and_thread_execution_policy*>(underlying_obj->ptr));
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


                template<typename Op, ternary_state op_action_type, absolute_base::Is_String_Or_Numeric Lhs_t>
                inline typename std::conditional<op_action_type == true, void, bool>
                    op_generator(Lhs_t& first_arg,const Polymoprhic_extensible_engine second_arg){
                        constexpr if(std::is_same_v(Lhs_t, uintptr_t)){
                        runtime_branching_using_only_second_arg<Op, op_action_type, uintptr_t>(first_arg,second_arg);
                        }                        
                        else if(std::is_same_v(Lhs_t, intptr_t)){
                        runtime_branching_using_only_second_arg<Op, op_action_type, intptr_t>(first_arg,second_arg);
                        }
                        else if(std::is_same_v(Lhs_t, long double)){
                        runtime_branching_using_only_second_arg<Op, op_action_type, long double>(first_arg,second_arg);
                        }
                        else if(std::is_same_v(Lhs_t, std::string)){
                        runtime_branching_using_only_second_arg<Op, op_action_type, std::string>(first_arg,second_arg);
                        }
                    }
                  template<typename Op, ternary_state op_action_type, absolute_base::Is_String_Or_Numeric Rhs_t>
                  inline typename std::conditional<op_action_type == true, void, bool>
                    op_generator(const Polymoprhic_extensible_engine first_arg,const Rhs_t& second_arg){
                        constexpr if(std::is_same_v(Lhs_t, uintptr_t)){
                        runtime_branching_using_only_first_arg<Op, op_action_type, uintptr_t>(first_arg,second_arg);
                        }                        
                        else if(std::is_same_v(Rhs_t, intptr_t)){
                        runtime_branching_using_only_first_arg<Op, op_action_type, intptr_t>(first_arg,second_arg);
                        }
                        else if(std::is_same_v(Rhs_t, long double)){
                        runtime_branching_using_only_first_arg<Op, op_action_type, long double>(first_arg,second_arg);
                        }
                        else if(std::is_same_v(Rhs_t, std::string)){
                        runtime_branching_using_only_first_arg<Op, op_action_type, std::string>(first_arg,second_arg);
                        }
                    }
                template<typename Op, ternary_state op_action_type>
                inline typename std::conditional<op_action_type == true, void, bool>
                    void_op_generator(const Polymoprhic_extensible_engine first_arg,const Polymoprhic_extensible_engine second_arg){
                    switch(produce_jump_index(first_arg.tag, second_arg.tag)){
                        /* --- Full Outer Dispatch Table Dispatch for first ARG(also known as Lhs) (using macros); the code generated would be a flat map. The macro takes care of the tags or both args--- */
                    
                        // [beginning(0 index) - 05): High-Operand Specialized
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, std::string, first_arg, second_arg, Type_tag::string_tag_for_15_plus_operand_ops)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, uintptr_t,   first_arg, second_arg, Type_tag::uintptr_tag_for_15_plus_operand_ops)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, intptr_t,    first_arg, second_arg, Type_tag::intptr_tag_for_15_plus_operand_ops)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, long double, first_arg, second_arg,Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops)
                        
                        // [05 - 9): Scalar Primitives
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, long double, first_arg, second_arg,Type_tag::long_double_tag_implementation_defined_size)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, uintptr_t,   first_arg, second_arg,Type_tag::uintptr_tag)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, std::string, first_arg, second_arg,Type_tag::string_tag)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, intptr_t,    first_arg, second_arg,Type_tag::intptr_tag)
                        
                        // [9 - 14): Containers
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, 
                        No_tag_template_type_info<std::vector<std::string>>,         first_arg,second_arg,Type_tag::vector_string)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, 
                        No_tag_template_type_info<std::vector<uintptr_t>>,           first_arg,second_arg,Type_tag::vector_uintptr)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, 
                        No_tag_template_type_info<std::vector<intptr_t>>,            first_arg,second_arg,Type_tag::vector_intptr)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, 
                        No_tag_template_type_info<std::vector<long double>>,         first_arg,second_arg,Type_tag::vector_long_double_tag_implementation_defined_size)
                        FLAAAT_JuMPEnTeRYGeNAraT0r(op, op_action_type, 
                        Nested_type_info,                                            first_arg,second_arg,Type_tag::nested_type_with_dynamic_container)
                        
                        default:
                            throw std::string{"Unimplemented type"};
                        
                        }    
                    
                    }
    
            };
            std::vector<std::vector<Extented_type_info>> vector_containing_types;
            std::deque<std::vector<Extented_type_info>> deque_containing_types;
            std::list<std::vector<Extented_type_info>> list_containing_types;
            std::forward_list<std::vector<Extented_type_info>> forward_list_containing_types;
            std::map<uintptr_t,std::vector<Extented_type_info>> map_containing_types;
            std::unordered_map<uintptr_t,std::vector<Extented_type_info>> hash_map_containing_types;
            std::array<std::vector<Extented_type_info>, 100> array_containing_types{{}};
            inline Polymoprhic_extensible_engine object_and_type_factory(const Extented_type_info& info, const std::string& string_to_read_from, 
                std::string:size_type* pos )
            {
                uintptr_t size_to_preallocate=0;
                
                switch(info.tag){
                    case Type_storage_facility::type_in_array_tag:
                        Extented_type_info.index
                    case Type_storage_facility::type_in_vector_tag:
                    
                    case Type_storage_facility::type_in_deque_tag:
                    
                    case Type_storage_facility::type_in_map_tag:
                    
                    case Type_storage_facility::type_in_hash_map_tag:
                    
                    case Type_storage_facility::type_in_list:
                    
                    case Type_storage_facility::type_in_forward_list:

                    case Type_storage_facility::newly_defined_temp_type_for_new_obj:

                    case Type_storage_facility::just_trying_to_define_a_new_type_without_making_any_objects:

                    case Type_storage_facility::just_trying_to_define_a_new_type_without_making_any_objects:
                    
                    
                }
      
            }
           
            


                
            



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








































































