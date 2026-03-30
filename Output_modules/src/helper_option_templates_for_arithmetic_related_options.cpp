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
            inline T read_from_string(const std::string& string_to_read_from, std::string:: std::size_type* pos) {
                if constexpr (std::is_same_v<T, std::string>) {
                    return read_string_from_string_at_a_position(string_to_read_from, pos);
                }
                else {
                    return absolute_base::read_number_from_string_at_a_position<T>(string_to_read_from, pos);
                }
            }

            template <absolute_base::Is_String_Or_Numeric T, bool read_from_x_or_y>
            inline T read_from_string(const std::string& x, const std::string& y, std::string:: std::size_type* x_pos, std::string:: std::size_type* y_pos) {
                constexpr if (read_from_x_or_y) {
                    read_from_string(x, x_pos);
                }
                else {
                    read_from_string(y, y_pos);

                }
            }
            template <bool read_from_x_or_y>
            inline bool read_from_string<bool>(const std::string& x, const std::string& y, std::string:: std::size_type* x_pos, std::string:: std::size_type* y_pos) {
                constexpr if (read_from_x_or_y) {
                    absolute_base::convert_to_bool(x, x_pos);
                }
                else {
                    absolute_base::convert_to_bool(y, y_pos);

                }
            }
            template <bool read_from_x_or_y>
            inline char read_from_string<char>(const std::string& x, const std::string& y, std::string:: std::size_type* x_pos, std::string:: std::size_type* y_pos) {
                constexpr if (read_from_x_or_y) {
                    absolute_base::convert_to_char(x, x_pos);
                }
                else {
                    absolute_base::convert_to_char(y, y_pos);

                }
            }
            template <>
            inline char read_from_string<char>(const std::string& y, std::string:: std::size_type* y_pos) {
                
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
                std::string:: std::size_type position = 0;
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
                void pump(std::string* string_to_pump_to, std::string:: std::size_type* output_string_position) {
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
                    reference_to_vector_of_nested_for_gpu_ops,
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

            //notice i had to define extra functions for forward lists
           enum class Type_storage_facility: uint8_t{
                types_in_array_tag=0,
                types_in_vector_tag=1,
                types_in_deque_tag=2,
                types_in_list,
                types_in_forward_list,
                types_in_map_tag,
                types_in_hash_map_tag,
                types_in_redis_map_tag,//todo
                get_from_back_then_pop_back_from_vector_tag,
                get_from_back_then_pop_back_from_deque_tag,
                get_from_back_then_pop_back_from_map_tag,
                get_from_back_then_pop_back_from_hash_map_tag,
                get_from_back_then_pop_back_from_redis_maps_tag,//todo
                get_from_back_then_pop_back_from_list,
                get_from_front_then_pop_front_from_forward_list,
                pop_many_times_then_get_from_back_then_pop_back_from_vector_tag,
                pop_many_times_then_get_from_back_then_pop_back_from_deque_tag,
                pop_many_times_then_get_from_back_then_pop_back_from_map_tag,
                pop_many_times_then_get_from_back_then_pop_back_from_hash_map_tag,
                pop_many_times_then_get_from_back_then_pop_back_from_redis_maps_tag,//todo
                pop_many_times_then_get_from_back_then_pop_back_from_list,
                pop_many_times_then_get_from_front_then_pop_front_from_forward_list,
                newly_defined_temp_type_for_new_obj,
                //notice how you cant push the a array because thats obviously not possible
                newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_vector_tag,
                newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_deque_tag,
                newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_map_tag,
                newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_hash_map_tag,
                newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_redis_map_tag,//todo
                newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_list_tag,
                newly_defined_permenant_type_for_new_obj_type_to_be_pushed_at_front_of_forward_list_tag,
            };
            enum class Which_type_facility_to_change: uint8_t{
                change_array_tag=0,
                change_vector_tag=1,
                change_deque_tag=2,
                change_map_tag=3,
                change_hash_map_tag,
                change_redis_map_tag,//todo
                change_list_tag,
                change_forward_list_tag
            };            
            enum class Which_type_facility_to_change_part_of_and_how: uint8_t{
                change_array_tag_do_it_non_sequentially,
                change_vector_tag_do_it_non_sequentially,
                change_deque_tag_do_it_non_sequentially,
                change_map_tag_do_it_non_sequentially,
                change_hash_map_tag_do_it_non_sequentially,
                change_list_tag_do_it_non_sequentially,
                change_forward_list_tag_do_it_non_sequentially,
                change_array_tag_do_it_parrallely,
                change_vector_tag_do_it_parrallely,
                change_deque_tag_do_it_parrallely,
                change_map_tag_do_it_parrallely,
                change_hash_map_tag_do_it_parrallely,
                change_redis_map_tag_do_it_parrallely,//todo
                change_list_tag_do_it_parrallely,
                change_forward_list_tag_do_it_parrallely,
            };
            enum class Which_type_facility_to_push_to_and_how: uint8_t{
                push_to_vector_tag=1,
                push_to_deque_tag=2,
                push_to_map_tag=3,
                push_to_hash_map_tag,
                push_to_redis_map_tag,//todo
                push_to_list_tag,
                push_to_front_of_forward_list_tag,      
            };
            enum class Which_type_facility_to_insert_into_and_how: uint8_t{
                insert_into_vector_tag=1,
                insert_into_deque_tag=2,
                insert_into_map_tag=3,
                insert_into_push_to_hash_map_tag,
                insert_into_redis_map_tag,//todo
                insert_into_list_tag,
                insert_into_front_of_forward_list_tag,      
            };
            enum class Which_type_facility_to_pop: uint8_t{
                pop_from_array_tag=0,
                pop_from_vector_tag=1,
                pop_from_deque_tag=2,
                pop_from_map_tag=3,
                pop_from_hash_map_tag,
                pop_from_redis_map_tag,//to do
                pop_from_list_tag,
                pop_from_front_of_forward_list_tag,
            };
            enum Monolothic_resource_index: uint8_t{
            monolithic_buffer_resource_index=0,
            all_elements_size_uintptr_t_index=1,
            };
            static constexpr auto indexes_to_skip = std::max(monolithic_buffer_resource_index, all_elements_size_uintptr_t_index);
            template<typename class_in_monolithic_buffer_and_element_size_is_stroed>
            static constexpr auto extra_size_reserve_in_monolithic_buffer= 
            sizeof(class_in_which_monolithic_buffer_and_element_size_is_stored*2)+
            sizeof(std::pmr::monotonic_buffer_resource::monotonic_buffer_resource)+sizeof(std::size_t);
            enum class Thread_policy_t : uint8_t {
            single_thread_exec,
            unsequenced_parrallel_exec
            }; //notice that all operations are unsequenced
            struct Nested_type_info{
                Type_tag_for_input tag;
                Thread_policy_t execution_policy;
                void* ptr;
            };
            template<typename T>
            struct No_tag_template_type_info{
            using underlying_container= t;
            Thread_policy_t execution_policy;
            T ptr;
            //Nested_type_info resolves to  No_tag_template_type_info
            //vectors of primitive types and strings are wrapped inside No_tag_template_type_info
            };
            namespace{
                /*To truly understand how i finished this whole namespace you have to realize that I spent 3 days on it
                , but even then could only finish the logical framework(base implementation functions) and 
                around (5-8) interface functions. Then I asked AI to finish the rest, while writing the number and task of each 
                interface functions to be finished right next to the apropriate enums. This technique worked becuase 
                in just 2 commits, most of the work was complete. This further complements the long standing foundational
                notion that AI is only good at pattern recognitionm, and that humans are still important for providing 
                the base for the pattern recognition tool to scan and then replicate. This also leads to the thought that
                what if programming could be revolutionarized with a namespace to enum mapping, that is that there would be 
                enum classes provide a class of actions, and enemurators name each one of them, then namespaces provide
                interface to the each of those enemurators actions of a enum class on a specific context or obj.
                ofcourse namespaces can still be used for grouping those interface functions, but a new construct would exist, 
                to map enum classees to these actions by taking a object or a group of objects as arguments. Each
                action would have its own requirements just like templates can have using C++ concepts. You should probably 
                provide some samples to better help AI. Now The usefulness of this expands as the scale does.
                Implementations functions should ofcourse be able to  use other interface functions, in order to 
                scale well and to allow for recursive patterns in these structures.
                most useful application of such programming style would probably be in programming networking protocols, but 
                even without AI this technique can enhance languages, if compilers found a way to support it. Think of 
                it as templates 2.0 with actions in the enum class chosen at runtime, just like in my program. AI
                is a black box and i cant just claim that I found a great way to use it, but what i can say is that 
                AI would in some way make us invent faith in it, precisely because its a black box. Religions
                as we know it are faith and we all agree to disagree becuase its faith that makes us agree on 
                a religion. The same could be said about AI in a few years, with each person claiming that his
                technique is the best. This all bowls down to the points:
                1. programming languages should support more advance forms of run time polymorphism to avoid
                blind faith in the capabilities of AI.
                2. Tools should be invented to Monitor and study every neural network path of a these large
                language models.
                The second point might be far fetched since AI models are hundreds of complex transformations(each
                taking billions of inputs nodes and producing billions of output nodes, but
                if we as human beings unite, we can monitor and figure out what those transformations mean and how to
                utilize them. The first step would probably to invent programming languages specifically for creating,
                ,deploying, managing, and mantaining these large language models.
                I know that this comment should not exist here, but i spent 2-3 months on this single file, 
                and since its almsot done, I thought I should spend a few minutes on what I learned in this 
                long journey.
                In shorter words, the issues with current runtime polymorphism is:
                there is no way to do single dispatch based on value since functions cant be overloaded using values and 
                virtual functions cant be templates.
                Single Dispatch is too expensive for systems programming, in particular, ddr4/ddr5 rams have very high throughput,
                which infers that fetching a vtable pointer will fill the cache with junk around vtable pointer meanhwile 
                ddr5 latency isnt high as well, so any fetch for data that might be far far away is discouraged.
                In my case, i couldve first made a base class providing a virtual function call(Func F, Args... args)
                then derieved classes of that base class would implement that function by making the first argument in args be
                the desired container class that i want to pass. Then using a factory function i return a  base class unique ptr to a
                allocated derieved class, the dereived class would be chosen based on switch case statements. In the end to implement
                the push, pop, change, etc functions, i could just called the factory function and then used the resulting unique ptr
                to pass a implementation function as F(and its arguments) to the pointer->call() function, or to use std::variant, 
                where the types are of container refrences.
                The reason that i avoided all this was because of the over head of new and delete, and the overhead of accessing 
                the vtable ptr.
                A fix might be to provide run time templates: func_a<><runtime template arguments> or 
                template_func_a<template args><runtime template arguments>. A JIT compiler would exist for lazy 
                evaluation of any functions whose runtime template isnt explicitly instantation, in which
                case a compiler would omit warnings to tell the user that JIT is attached. These features would 
                revolutionarize the role of c++ in Interpreted languages and help the tech ecosystem a lot.
                The lack of such features makes me look towards C# because C# does support JIT for instantiation of generics,
                so i really hope C++26 have support for runtime templates. There are many other fixes that i mailed to the cpp
                standard comittee.

                Again, i know this comment isnt something that is should put in some code file, but i really love  talking about
                my journey, even if no one is listening
                
                
                */
                
                template<typename Container_t>
                struct Iterator_subscript_index{
                using type=typename std::iterator_traits<typename Container_t::iterator>::difference_type;
                };
                template<typename Container_t>
                using Iterator_subscript_index_t= Iterator_subscript_index<Container_t>::type;
                

                struct Type_info_t{
                    std::vector<Type_tag> type_info_of_all;
                    using Container_t= std::vector<Type_tag>;
                    std::size_t size_of_all;
                };
                namespace type_information_storage_facilities_and_functions_to_access_them{
                    namespace type_information_storage_facilities{
                        std::vector<Type_info_t> vector_containing_type_collections;
                        std::deque<Type_info_t> deque_containing_type_collections;
                        std::vector<Type_info_t> map_containing_type_collections; 
                        std::vector<Type_info_t> hash_map_containing_type_collections;
                        std::list<Type_info_t> list_containing_type_collections;
                        std::forward_list<Type_info_t> forward_list_containing_type_collections;
                        std::array<Type_info_t, 100> array_containing_types{};
                    }
                    using namespace type_information_storage_facilities;
                    namespace main_interface_to_get_type_information{
                            namespace helper_implementation_functions{
                                template<typename Container_t>
                                struct Get_cont_size_type{
                                using type= std::size_t;
                                };
                                template<typename Container_t>
                                requires requires { typename Container_t::size_type; }
                                struct Get_cont_size_type<Container_t>{
                                using type= typename Container_t::size_type;
                                };
                                template<typename Container_t>
                                using Get_cont_size_type_t= typename Get_cont_size_type<Container_t>::type;
                                template <size_t Size>
                                struct Integer_type_selector {
                                    using type = std::uintmax_t;
                                };
                                
                                template <>
                                struct Integer_type_selector<8> {
                                    using type = std::uint8_t;
                                };
                                
                                template <>
                                struct Integer_type_selector<16> {
                                    using type = std::uint16_t;
                                };
                                
                                template <>
                                struct Integer_type_selector<32> {
                                    using type = std::uint32_t;
                                };
                                
                                template <>
                                struct Integer_type_selector<64> {
                                    using type = std::uint64_t;
                                };
                                template <size_t Size>
                                using Integer_type_selector_t= typename Integer_type_selector<Size>::type;


                                using Subscript_for_vector_of_type_tag=Get_cont_size_type_t<std::vector<Type_tag>>;



                                inline std::size_t size_of_the_underlying_type_of_every_tag(Type_tag tag) {
                                    switch (tag) {
                                        /* --- High-Operand Specialized Tags --- */
                                        case Type_tag::string_tag_for_15_plus_operand_ops:
                                            return sizeof(std::string);
                                        case Type_tag::uintptr_tag_for_15_plus_operand_ops:
                                            return sizeof(std::uintptr_t);
                                        case Type_tag::intptr_tag_for_15_plus_operand_ops:
                                            return sizeof(std::intptr_t);
                                        case Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops:
                                            return sizeof(long double);
                                        /* --- Scalar Primitive Types --- */
                                        case Type_tag::long_double_tag_implementation_defined_size:
                                            return sizeof(long double);
                                        case Type_tag::uintptr_tag:
                                            return sizeof(std::uintptr_t);
                                        case Type_tag::string_tag:
                                            return sizeof(std::string);
                                        case Type_tag::intptr_tag:
                                            return sizeof(std::intptr_t);
                                        /* --- Contiguous & Dynamic Containers --- */
                                        case Type_tag::vector_string:
                                            return sizeof(std::vector<std::string>);
                                        case Type_tag::vector_uintptr:
                                            return sizeof(std::vector<std::uintptr_t>);
                                        case Type_tag::vector_intptr:
                                            return sizeof(std::vector<std::intptr_t>);
                                        case Type_tag::vector_long_double_tag_implementation_defined_size:
                                            return sizeof(std::vector<long double>);
                                        case Type_tag::nested_type_with_dynamic_container:
                                            return sizeof(Nested_type_info);
                                
                                        default:
                                            throw std::string{"size unknown"}; 
                                    }
                                }
                                inline Type_info_t get_collections_of_types_from_string(const std::string& string_to_read_from, std::string::size_type* pos){
                                    Type_info_t temp_type{Type_info_t::Container_t{read_from_string<Get_cont_size_type_t<Type_info_t::Container_t>>(string_to_read_from, pos)}, 0};
                                    std::size_t size= 0;
                                    for(auto &x:temp_type.type_info_of_all){
                                        auto tag= static_cast<Type_tag>(read_from_string<Integer_type_selector_t
                                            <Integer_type_selector<sizeof(Type_tag)>::value>>(string_to_read_from, pos));
                                        x= tag;
                                        size+=size_of_the_underlying_type_of_every_tag(tag);
                                    }
                                    temp_type.size_of_all=size;
                                    
                                    return temp_type;
                                }
                                template<template<typename> class Container_t_outer>
                                inline Container_t_outer<Type_info_t> get_list_of_collections_of_types_from_string_the_list_can_be_of_any_container_type(const std::string& string_to_read_from, std::string::size_type* pos){
                                    auto outer_size= read_from_string<Get_cont_size_type_t<Container_t_outer<Type_info_t>>>(string_to_read_from, pos);
                                    auto inner_size= read_from_string<Get_cont_size_type_t<Type_info_t::Container_t>>(string_to_read_from, pos);
                                    
                                    Container_t_outer<Type_info_t> temp_type(outer_size, Type_info_t{{}, inner_size});
                                    for(auto &y:temp_type){
                                        y= get_collections_of_types_from_string(string_to_read_from, pos);
                                    }
                                    return temp_type;
                                }
                                
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.push_back(std::declval<typename Container_t::value_type>()); }
                                inline void push_back_into_container(Container_t& obj, typename Container_t::value_type val){
                                    obj.push_back(val);
                                }
                                
                                template<typename Container_t, typename Value_type>
                                requires requires(Container_t<Value_type> obj) { obj.begin()++; }
                                Value_type& at_for_containers_that_dont_support_it(Container_t<Value_type>& obj, typename Iterator_subscript_index_t<Container_t<Value_type>>::type index){
                                    if(obj.empty()){
                                        throw std::string{"out of bound error while subscripting an empty container that dosent support .at()"};
                                    }
                                    auto it= obj.begin();
                                    auto end_=obj.end();
                                    for(; it!=end_; it++){
                                        if(index-- == 0) return *it;
                                    }
                                    throw std::string{"out of bound error while subscripting a container that dosent support .at()"};
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.pop_back(); obj.empty(); }
                                inline void pop_back_container(Container_t& obj){
                                    if(!obj.empty()){
                                        obj.pop_back();                                    
                                    }
                                    else{
                                        throw std::string{"attempt to destroy an empty vector that was supposed to container lists of collections of types "};
                                    }  
                                }                                
                                template<typename Container_t, typename Value_type>
                                requires requires(Container_t<Value_type> obj) { obj.pop_front(); obj.empty(); }
                                inline void pop_front_from_forward_list(Container_t<Value_type>& obj){
                                    if(!obj.empty()){
                                        obj.pop_front();                                    
                                    }
                                    else{
                                        throw std::string{"attempt to destroy an empty vector that was supposed to container lists of collections of types "};
                                    }  
                                }
                                template<typename Container_t>
                                inline void pop_back_container_many_times(Container_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                auto index= read_from_string<Get_cont_size_type_t<Container_t>>(string_to_read_from, pos);
                                for(int i= 0; i++<index;){pop_back_container(obj);}
                                }
                                template<typename Container_t>
                                inline void pop_front_container_of_forward_list_many_times(Container_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                auto inner_size= read_from_string<Get_cont_size_type_t<Container_t>>(string_to_read_from, pos);
                                for(int i= 0; i++<inner_size;){pop_front_from_forward_list(obj);}
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.back(); obj.pop_back(); obj.empty(); }
                                inline typename Container_t::value_type get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back(Container_t& obj){
                                    if(!obj.empty()){
                                        auto temp = std::move(obj.back());
                                        obj.pop_back();            
                                        return temp;
                                    }
                                    else{
                                        throw std::string{"attempt to destroy an empty vector that was supposed to container lists of collections of types "};
                                    }  
                                }
                                template<typename Container_t, typename Value_type>
                                requires requires(Container_t<Value_type> obj) { obj.front(); obj.pop_front(); obj.empty(); }
                                inline Value_type get_element_at_front_then_pop_front_then_return_the_element_you_retrieved_before_pop_back(Container_t<Value_type>& obj){
                                    if(!obj.empty()){
                                        auto temp = std::move(obj.front());
                                        obj.pop_front();            
                                        return temp;
                                    }
                                    else{
                                        throw std::string{"attempt to destroy an empty vector that was supposed to container lists of collections of types "};
                                    }  
                                }
                                template<typename Container_t>
                                inline typename Container_t::value_type pop_back_many_times_then_get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back(const std::string& string_to_read_from, std::string::size_type* pos, Container_t& obj){
                                    auto index= 
                                    read_from_string<Get_cont_size_type_t<Container_t>>(string_to_read_from, pos);
                                    for(int i= 0; i++<index;){pop_back_container(obj);}
                                    return get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back(obj);
                                }
                                template<typename Container_t, typename Value_type>
                                inline Value_type pop_front_many_times_then_get_element_at_front_then_pop_front_then_return_the_element_you_retrieved_before_pop_back(Container_t<Value_type>& obj,  const std::string& string_to_read_from, std::string::size_type* pos){
                                    auto index= 
                                    read_from_string<Get_cont_size_type_t<Container_t>>(string_to_read_from, pos);
                                    for(int i= 0; i++<index;){pop_front_from_forward_list(obj);}
                                    return get_element_at_front_then_pop_front_then_return_the_element_you_retrieved_before_pop_back(obj);
                                    
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.at(std::declval<Get_cont_size_type_t<Container_t>>()); }
                                inline typename Container_t::value_type& at_for_all_contianers(Container_t& obj, Get_cont_size_type_t<Container_t> index) {
                                   return obj.at(index);
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { std::next(obj.begin(), std::declval<Iterator_subscript_index_t<Container_t>>()); }
                                inline typename Container_t::value_type& at_for_all_contianers(Container_t& obj, Iterator_subscript_index_t<Container_t> index) {
                                   return *(std::next(obj.begin(), index));
                                }
                                template<typename Container_t, typename execution_policy>
                                requires requires(Container_t obj) { std::next(obj.begin(), std::declval<Iterator_subscript_index_t<Container_t>>()); }
                                inline void change_part_of_the_container_using_an_execution_policy(Container_t& obj,  const std::string& string_to_read_from, std::string::size_type* pos, execution_policy policy){                                       
                                    auto index_where_the_collection_is_at= 
                                    read_from_string<Get_cont_size_type_t<Container_t>>(string_to_read_from, pos);
                                    auto index_inside_the_collection_itself= 
                                    read_from_string<Iterator_subscript_index_t<Container_t>>(string_to_read_from, pos);
                                    auto& collection_to_change_part_of=
                                    at_for_all_contianers(obj,index_where_the_collection_is_at);
                                    auto type_info_to_change_using= get_collections_of_types_from_string
                                    (string_to_read_from, pos);
                                    if(collection_to_change_part_of.type_info_of_all.size() >= static_cast<size_t>(index_inside_the_collection_itself)){
                                        std::copy(policy,type_info_to_change_using.type_info_of_all.begin(),
                                            type_info_to_change_using.type_info_of_all.end(),std::next(collection_to_change_part_of.type_info_of_all.begin(), index_inside_the_collection_itself));
                                    }
                                    else{
                                        throw std::string{"Attempt at writing to a list of collections of types passed the end"};
                                    }
                            }              

                                template<typename Container_t>
                                inline void change_part_of_the_container_non_sequentially(Container_t& obj,  const std::string& string_to_read_from, std::string::size_type* pos){                                       
                                    change_part_of_the_container_using_an_execution_policy(obj,string_to_read_from, pos, std::execution::unseq);
                            }
                                
                                template<typename Container_t>
                                inline void change_part_of_the_container_parrallely_and_also_unsequentially(Container_t& obj,  const std::string& string_to_read_from, std::string::size_type* pos){                                       
                                    change_part_of_the_container_using_an_execution_policy(obj,string_to_read_from, pos, std::execution::par_unseq);
                            }    
                                inline void push_same_many_times(Type_info_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                    using type_of_data_to_push=Type_info_t::Container_t::value_type;
                                    auto how_many_times= read_from_string<Get_cont_size_type_t<Type_info_t::Container_t>>(string_to_read_from, pos);
                                    auto what_to_push= static_cast<type_of_data_to_push>(
                                    read_from_string<Integer_type_selector_t<sizeof(type_of_data_to_push)>>(string_to_read_from, pos));
                                    
                                    for(int i=0; i<how_many_times; i++){
                                        obj.type_info_of_all.push_back(what_to_push);
                                    }
                                }
                                inline void push_many_newly_read_times(Type_info_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                    using type_of_data_to_push=Type_info_t::Container_t::value_type;
                                    auto how_many_times= read_from_string<Get_cont_size_type_t<Type_info_t::Container_t>>(string_to_read_from, pos);
                                    for(int i=0; i<how_many_times; i++){
                                        auto what_to_push= static_cast<type_of_data_to_push>(
                                        read_from_string<Integer_type_selector_t<sizeof(type_of_data_to_push)>>(string_to_read_from, pos));
                                        obj.type_info_of_all.push_back(what_to_push);
                                    }
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.push_back(std::declval<typename Container_t::value_type>()); }
                                inline void push_same_newly_read_many_times(Container_t& obj,const std::string& string_to_read_from, std::string::size_type* pos){
                                    auto type_info= get_collections_of_types_from_string(string_to_read_from, pos);
                                    auto how_many_times= read_from_string<Get_cont_size_type_t<Container_t>>(string_to_read_from, pos);
                                    for(int i=0; i<how_many_times; i++){
                                    obj.push_back(type_info);
                                    }
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.push_front(std::declval<typename Container_t::value_type>()); }
                                inline void push_same_newly_read_at_front_many_times(Container_t& obj,const std::string& string_to_read_from, std::string::size_type* pos){
                                    auto type_info= get_collections_of_types_from_string(string_to_read_from, pos);
                                    auto how_many_times= read_from_string<Get_cont_size_type_t<Container_t>>(string_to_read_from, pos);
                                    for(int i=0; i<how_many_times; i++){
                                    obj.push_front(type_info);
                                    }
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.push_back(std::declval<typename Container_t::value_type>()); }
                                inline void push_newly_read_many_times(Container_t& obj,const std::string& string_to_read_from, std::string::size_type* pos){
                                    auto list_of_collections_to_push=get_list_of_collections_of_types_from_string_the_list_can_be_of_any_container_type<std::vector>(string_to_read_from, pos);
                                    for(auto &x: list_of_collections_to_push){
                                    obj.push_back(x);
                                    }
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.push_front(std::declval<typename Container_t::value_type>()); }
                                inline void push_newly_read_at_front_many_times(Container_t& obj,const std::string& string_to_read_from, std::string::size_type* pos){
                                    auto list_of_collections_to_push=get_list_of_collections_of_types_from_string_the_list_can_be_of_any_container_type<std::vector>(string_to_read_from, pos);
                                    for(auto &x: list_of_collections_to_push){
                                    obj.push_front(x);
                                    }
                                }
                                inline void insert_single_element_into_type_info_container_at_specified_index(Type_info_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                    using type_of_data_to_insert=Type_info_t::Container_t::value_type;
                                    auto index_to_insert_at= read_from_string<Subscript_for_vector_of_type_tag>(string_to_read_from, pos);
                                    auto what_to_insert= static_cast<type_of_data_to_insert>(
                                    read_from_string<Integer_type_selector_t<sizeof(type_of_data_to_insert)>>(string_to_read_from, pos));
                                    obj.type_info_of_all.insert(std::next(obj.type_info_of_all.begin(), index_to_insert_at), what_to_insert);
                                }
                                inline void insert_many_same_elements_into_type_info_container_at_specified_index(Type_info_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                    using type_of_data_to_insert=Type_info_t::Container_t::value_type;
                                    auto index_to_insert_at= read_from_string<Subscript_for_vector_of_type_tag>(string_to_read_from, pos);
                                    auto how_many_times= read_from_string<Get_cont_size_type_t<Type_info_t::Container_t>>(string_to_read_from, pos);
                                    auto what_to_insert= static_cast<type_of_data_to_insert>(
                                    read_from_string<Integer_type_selector_t<sizeof(type_of_data_to_insert)>](string_to_read_from, pos));
                                    obj.type_info_of_all.insert(std::next(obj.type_info_of_all.begin(), index_to_insert_at), how_many_times, what_to_insert);
                                }
                                inline void insert_many_newly_read_elements_into_type_info_container_at_specified_index(Type_info_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                    using type_of_data_to_insert=Type_info_t::Container_t::value_type;
                                    auto index_to_insert_at= read_from_string<Subscript_for_vector_of_type_tag>(string_to_read_from, pos);
                                    auto how_many_times= read_from_string<Get_cont_size_type_t<Type_info_t::Container_t>>(string_to_read_from, pos);
                                    std::vector<type_of_data_to_insert> temp;
                                    for(int i=0; i<how_many_times; i++){
                                        auto what_to_insert= static_cast<type_of_data_to_insert>(
                                        read_from_string<Integer_type_selector_t<sizeof(type_of_data_to_insert)>>(string_to_read_from, pos));
                                        temp.push_back(what_to_insert);
                                    }
                                    obj.type_info_of_all.insert(std::next(obj.type_info_of_all.begin(), index_to_insert_at), temp.begin(), temp.end());
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.insert(std::declval<typename Container_t::iterator>(), std::declval<std::size_t>(), std::declval<typename Container_t::value_type>()); }
                                inline void insert_same_newly_read_many_times_at_specified_index(Container_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                    auto type_info= get_collections_of_types_from_string(string_to_read_from, pos);
                                    auto index_to_insert_at= read_from_string<Iterator_subscript_index_t<Container_t>>(string_to_read_from, pos);
                                    auto how_many_times= read_from_string<Get_cont_size_type_t<Container_t>>(string_to_read_from, pos);
                                    obj.insert(std::next(obj.begin(), index_to_insert_at), how_many_times, type_info);
                                }
                                template<typename Container_t>
                                requires requires(Container_t obj) { obj.insert_after(std::declval<typename Container_t::iterator>(), std::declval<std::size_t>(), std::declval<typename Container_t::value_type>()); }
                                inline void insert_same_newly_read_many_times_at_specified_index_forward_list(Container_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                    auto type_info= get_collections_of_types_from_string(string_to_read_from, pos);
                                    auto index_to_insert_at= read_from_string<Iterator_subscript_index_t<Container_t>>(string_to_read_from, pos);
                                    auto how_many_times= read_from_string<Get_cont_size_type_t<Container_t>>(string_to_read_from, pos);
                                    obj.insert_after(std::next(obj.begin(), index_to_insert_at), how_many_times, type_info);
                                }
                                inline void pop_many_from_type_info_container(Type_info_t& obj, const std::string& string_to_read_from, std::string::size_type* pos){
                                    auto how_many_times= read_from_string<Get_cont_size_type_t<Type_info_t::Container_t>>(string_to_read_from, pos);
                                    for(int i=0; i<how_many_times; i++){
                                        pop_back_container(obj.type_info_of_all);
                                    }
                                }
                            }
                            using namespace helper_implementation_functions;
                            inline Type_info_t& get_type_info_from_the_specified_storage_facility
                            (const std::string& string_to_read_from, std::string::size_type* pos){
                                Type_storage_facility what_to_do= static_cast<Type_storage_facility>(
                                    read_from_string<uint8_t>(string_to_read_from, pos));
                                    switch(what_to_do){
                                        case Type_storage_facility::types_in_array_tag:
                                            return array_containing_types.at(read_from_string
                                                <Get_cont_size_type_t<decltype(array_containing_types)>>
                                                (string_to_read_from, pos));
                                        case Type_storage_facility::types_in_vector_tag:
                                            return vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos));                                        
                                        case Type_storage_facility::types_in_deque_tag:
                                            return deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos));   
                                        case Type_storage_facility::types_in_map_tag:
                                            return map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)); 
                                        case Type_storage_facility::types_in_hash_map_tag:
                                            return hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos));   
                                        case Type_storage_facility::types_in_list:
                                            return at_for_containers_that_dont_support_it
                                                (list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos));
                                        case Type_storage_facility::types_in_forward_list:
                                            return at_for_containers_that_dont_support_it
                                                (forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos));
                                        case Type_storage_facility::get_from_back_then_pop_back_from_vector_tag:
                                            return get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (vector_containing_type_collections);                                    
                                        case Type_storage_facility::get_from_back_then_pop_back_from_deque_tag:
                                            return get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (deque_containing_type_collections);                            
                                        case Type_storage_facility::get_from_back_then_pop_back_from_map_tag:
                                            return get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (map_containing_type_collections);                                                                            
                                        case Type_storage_facility::get_from_back_then_pop_back_from_hash_map_tag:
                                            return get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (hash_map_containing_type_collections);                                            
                                        case Type_storage_facility::get_from_back_then_pop_back_from_list:
                                            return get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (list_containing_type_collections);                                        
                                        case Type_storage_facility::get_from_front_then_pop_front_from_forward_list:
                                            return get_element_at_front_then_pop_front_then_return_the_element_you_retrieved_before_pop_back
                                                   (forward_list_containing_type_collections);   
                                        case Type_storage_facility::pop_many_times_then_get_from_back_then_pop_back_from_vector_tag:
                                            return pop_back_many_times_then_get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (string_to_read_from, pos, vector_containing_type_collections);                                    
                                        case Type_storage_facility::pop_many_times_then_get_from_back_then_pop_back_from_deque_tag:
                                            return pop_back_many_times_then_get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (string_to_read_from, pos, deque_containing_type_collections);                            
                                        case Type_storage_facility::pop_many_times_then_get_from_back_then_pop_back_from_map_tag:
                                            return pop_back_many_times_then_get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (string_to_read_from, pos, map_containing_type_collections);                                                                            
                                        case Type_storage_facility::pop_many_times_then_get_from_back_then_pop_back_from_hash_map_tag:
                                            return pop_back_many_times_then_get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (string_to_read_from, pos, hash_map_containing_type_collections);                                            
                                        case Type_storage_facility::pop_many_times_then_get_from_back_then_pop_back_from_list:
                                            return pop_back_many_times_then_get_element_at_back_then_pop_back_then_return_the_element_you_retrieved_before_pop_back
                                                   (string_to_read_from, pos, list_containing_type_collections);                                        
                                        case Type_storage_facility::pop_many_times_then_get_from_front_then_pop_front_from_forward_list:
                                            return pop_front_many_times_then_get_element_at_front_then_pop_front_then_return_the_element_you_retrieved_before_pop_back
                                                   (forward_list_containing_type_collections, string_to_read_from, pos);                                           
                                        case Type_storage_facility::newly_defined_temp_type_for_new_obj:
                                            return get_collections_of_types_from_string(string_to_read_from, pos);
                                        case Type_storage_facility::newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_vector_tag:
                                            {
                                            auto type_info=  get_collections_of_types_from_string(string_to_read_from, pos);
                                            vector_containing_type_collections.push_back(std::move(type_info));
                                            return vector_containing_type_collections.back();
                                            }
                                        case Type_storage_facility::newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_deque_tag:
                                            {
                                            auto type_info=  get_collections_of_types_from_string(string_to_read_from, pos);
                                            deque_containing_type_collections.push_back(std::move(type_info));
                                            return deque_containing_type_collections.back();
                                            }
                                        case Type_storage_facility::newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_list_tag:
                                            {
                                            auto type_info=  get_collections_of_types_from_string(string_to_read_from, pos);
                                            list_containing_type_collections.push_back(std::move(type_info));
                                            return list_containing_type_collections.back();
                                            }
                                        case Type_storage_facility::newly_defined_permenant_type_for_new_obj_type_to_be_pushed_at_front_of_forward_list_tag:
                                            {
                                            auto type_info=  get_collections_of_types_from_string(string_to_read_from, pos);
                                            forward_list_containing_type_collections.push_front(std::move(type_info));
                                            return forward_list_containing_type_collections.front();
                                            }
                                        case Type_storage_facility::newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_map_tag:
                                            {
                                            auto type_info=  get_collections_of_types_from_string(string_to_read_from, pos);
                                            map_containing_type_collections.push_back(std::move(type_info));
                                            return map_containing_type_collections.back();
                                            }
                                        case Type_storage_facility::newly_defined_permenant_type_for_new_obj_type_to_be_pushed_to_hash_map_tag:
                                            {
                                            auto type_info=  get_collections_of_types_from_string(string_to_read_from, pos);
                                            hash_map_containing_type_collections.push_back(std::move(type_info));
                                            return hash_map_containing_type_collections.back();
                                            }
                                        
                                        default:
                                            throw std::string{"invalid type location!!!"};
                                
                                    }
                                }
                                
                                inline void change_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        auto type_info=  get_collections_of_types_from_string(string_to_read_from, pos);
                                        Which_type_facility_to_change facility_to_change= 
                                        static_cast<Which_type_facility_to_change>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_change::change_array_tag:
                                            array_containing_types.at(read_from_string
                                                <Get_cont_size_type_t<decltype(array_containing_types)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;
                                        case Which_type_facility_to_change::change_vector_tag:
                                            vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;                                        
                                        case Which_type_facility_to_change::change_deque_tag:
                                            deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;   
                                        case Which_type_facility_to_change::change_map_tag:
                                            map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break; 
                                        case Which_type_facility_to_change::change_hash_map_tag:
                                            hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;   
                                        case Which_type_facility_to_change::change_list_tag:
                                            at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;
                                        case Which_type_facility_to_change::change_forward_list_tag:
                                            at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;   
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                inline void change_many_collections_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        auto type_info=  get_collections_of_types_from_string(string_to_read_from, pos);
                                        Which_type_facility_to_change facility_to_change= 
                                        static_cast<Which_type_facility_to_change>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_change::change_array_tag:
                                            array_containing_types.at(read_from_string
                                                <Get_cont_size_type_t<decltype(array_containing_types)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;
                                        case Which_type_facility_to_change::change_vector_tag:
                                            vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;                                        
                                        case Which_type_facility_to_change::change_deque_tag:
                                            deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;   
                                        case Which_type_facility_to_change::change_map_tag:
                                            map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break; 
                                        case Which_type_facility_to_change::change_hash_map_tag:
                                            hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;   
                                        case Which_type_facility_to_change::change_list_tag:
                                            at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;
                                        case Which_type_facility_to_change::change_forward_list_tag:
                                            at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos))= std::move(type_info);
                                            break;   
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                 inline void change_single_element_at_index_in_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_change facility_to_change= 
                                        static_cast<Which_type_facility_to_change>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        Type_tag element_to_change_with= 
                                        static_cast<Type_tag>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_change::change_array_tag:
                                            array_containing_types.at(read_from_string
                                                <Get_cont_size_type_t<decltype(array_containing_types)>>
                                                (string_to_read_from, pos)).type_info_of_all.at(read_from_string
                                                <Subscript_for_vector_of_type_tag>
                                                (string_to_read_from, pos))= element_to_change_with;
                                            break;
                                        case Which_type_facility_to_change::change_vector_tag:
                                            vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.at(read_from_string
                                                <Subscript_for_vector_of_type_tag>
                                                (string_to_read_from, pos))= element_to_change_with;
                                            break;                                        
                                        case Which_type_facility_to_change::change_deque_tag:
                                            deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.at(read_from_string
                                                <Subscript_for_vector_of_type_tag>
                                                (string_to_read_from, pos))= element_to_change_with;
                                            break;   
                                        case Which_type_facility_to_change::change_map_tag:
                                            map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.at(read_from_string
                                                <Subscript_for_vector_of_type_tag>
                                                (string_to_read_from, pos))= element_to_change_with;
                                            break; 
                                        case Which_type_facility_to_change::change_hash_map_tag:
                                            hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.at(read_from_string
                                                <Subscript_for_vector_of_type_tag>
                                                (string_to_read_from, pos))= element_to_change_with;
                                            break;   
                                        case Which_type_facility_to_change::change_list_tag:
                                            at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.at(read_from_string
                                                <Subscript_for_vector_of_type_tag>
                                                (string_to_read_from, pos))= element_to_change_with;
                                            break;
                                        case Which_type_facility_to_change::change_forward_list_tag:
                                            at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.at(read_from_string
                                                <Subscript_for_vector_of_type_tag>
                                                (string_to_read_from, pos))= element_to_change_with;
                                            break;   
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }

                                 inline void push_to_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_push_to_and_how facility_to_change= 
                                        static_cast<Which_type_facility_to_push_to_and_how>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        Type_tag element_to_change_with= 
                                        static_cast<Type_tag>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_push_to_and_how::push_to_vector_tag:
                                            vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.push_back(element_to_change_with);
                                            break;
                                        case Which_type_facility_to_push_to_and_how::push_to_deque_tag:
                                            deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.push_back(element_to_change_with);
                                            break;   
                                        case Which_type_facility_to_push_to_and_how::push_to_map_tag:
                                            map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.push_back(element_to_change_with);
                                            break; 
                                        case Which_type_facility_to_push_to_and_how::push_to_hash_map_tag:
                                            hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.push_back(element_to_change_with);
                                            break;   
                                        case Which_type_facility_to_push_to_and_how::push_to_list_tag:
                                            at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.push_back(element_to_change_with);
                                            break;
                                        case Which_type_facility_to_push_to_and_how::push_to_front_of_forward_list_tag:
                                            at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all.push_back(element_to_change_with);
                                            break;   
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                 inline void push_same_many_to_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_push_to_and_how facility_to_change= 
                                        static_cast<Which_type_facility_to_push_to_and_how>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_push_to_and_how::push_to_vector_tag:
                                            push_same_many_times
                                                (vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_push_to_and_how::push_to_deque_tag:
                                            push_same_many_times
                                                (deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_push_to_and_how::push_to_map_tag:
                                            push_same_many_times
                                                (map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break; 
                                        case Which_type_facility_to_push_to_and_how::push_to_hash_map_tag:
                                            push_same_many_times
                                                (hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_push_to_and_how::push_to_list_tag:
                                            push_same_many_times
                                                (at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_push_to_and_how::push_to_front_of_forward_list_tag:
                                            push_same_many_times
                                                (at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                 inline void push_many_newly_read_to_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_push_to_and_how facility_to_change= 
                                        static_cast<Which_type_facility_to_push_to_and_how>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_push_to_and_how::push_to_vector_tag:
                                            push_many_newly_read_times
                                                (vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_push_to_and_how::push_to_deque_tag:
                                            push_many_newly_read_times
                                                (deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_push_to_and_how::push_to_map_tag:
                                            push_many_newly_read_times
                                                (map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break; 
                                        case Which_type_facility_to_push_to_and_how::push_to_hash_map_tag:
                                            push_many_newly_read_times
                                                (hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_push_to_and_how::push_to_list_tag:
                                            push_many_newly_read_times
                                                (at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_push_to_and_how::push_to_front_of_forward_list_tag:
                                            push_many_newly_read_times
                                                (at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                 inline void pop_from_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_pop facility_to_change= 
                                        static_cast<Which_type_facility_to_pop>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_pop::pop_from_array_tag:
                                           pop_back_container
                                               (array_containing_types.at(read_from_string
                                                <Get_cont_size_type_t<decltype(array_containing_types)>>
                                                (string_to_read_from, pos)).type_info_of_all);
                                           break;
                                        case Which_type_facility_to_pop::pop_from_vector_tag:
                                           pop_back_container
                                               (vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all);
                                           break;                                        
                                        case Which_type_facility_to_pop::pop_from_deque_tag:
                                            pop_back_container
                                               (deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all);
                                            break;   
                                        case Which_type_facility_to_pop::pop_from_map_tag:
                                            pop_back_container
                                               (map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all);
                                            break; 
                                        case Which_type_facility_to_pop::pop_from_hash_map_tag:
                                            pop_back_container
                                               (hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all);
                                            break;   
                                        case Which_type_facility_to_pop::pop_from_list_tag:
                                            pop_back_container
                                               (at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all);
                                            break;
                                        case Which_type_facility_to_pop::pop_from_front_of_forward_list_tag:
                                            pop_front_from_forward_list
                                               (at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos)).type_info_of_all);
                                            break;
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                 inline void pop_many_from_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_pop facility_to_change= 
                                        static_cast<Which_type_facility_to_pop>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_pop::pop_from_array_tag:
                                           pop_many_from_type_info_container
                                               (array_containing_types.at(read_from_string
                                                <Get_cont_size_type_t<decltype(array_containing_types)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                           break;
                                        case Which_type_facility_to_pop::pop_from_vector_tag:
                                           pop_many_from_type_info_container
                                               (vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                           break;                                        
                                        case Which_type_facility_to_pop::pop_from_deque_tag:
                                           pop_many_from_type_info_container
                                               (deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_pop::pop_from_map_tag:
                                           pop_many_from_type_info_container
                                               (map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break; 
                                        case Which_type_facility_to_pop::pop_from_hash_map_tag:
                                           pop_many_from_type_info_container
                                               (hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_pop::pop_from_list_tag:
                                           pop_many_from_type_info_container
                                               (at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_pop::pop_from_front_of_forward_list_tag:
                                           pop_many_from_type_info_container
                                               (at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                 inline void insert_into_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_insert_into_and_how facility_to_change= 
                                        static_cast<Which_type_facility_to_insert_into_and_how>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_insert_into_and_how::insert_into_vector_tag:
                                            insert_single_element_into_type_info_container_at_specified_index
                                                (vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_insert_into_and_how::insert_into_deque_tag:
                                            insert_single_element_into_type_info_container_at_specified_index
                                                (deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_insert_into_and_how::insert_into_map_tag:
                                            insert_single_element_into_type_info_container_at_specified_index
                                                (map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break; 
                                        case Which_type_facility_to_insert_into_and_how::insert_into_push_to_hash_map_tag:
                                            insert_single_element_into_type_info_container_at_specified_index
                                                (hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_insert_into_and_how::insert_into_list_tag:
                                            insert_single_element_into_type_info_container_at_specified_index
                                                (at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_insert_into_and_how::insert_into_front_of_forward_list_tag:
                                            insert_single_element_into_type_info_container_at_specified_index
                                                (at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                 inline void insert_same_many_into_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_insert_into_and_how facility_to_change= 
                                        static_cast<Which_type_facility_to_insert_into_and_how>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_insert_into_and_how::insert_into_vector_tag:
                                            insert_many_same_elements_into_type_info_container_at_specified_index
                                                (vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_insert_into_and_how::insert_into_deque_tag:
                                            insert_many_same_elements_into_type_info_container_at_specified_index
                                                (deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_insert_into_and_how::insert_into_map_tag:
                                            insert_many_same_elements_into_type_info_container_at_specified_index
                                                (map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break; 
                                        case Which_type_facility_to_insert_into_and_how::insert_into_push_to_hash_map_tag:
                                            insert_many_same_elements_into_type_info_container_at_specified_index
                                                (hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_insert_into_and_how::insert_into_list_tag:
                                            insert_many_same_elements_into_type_info_container_at_specified_index
                                                (at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_insert_into_and_how::insert_into_front_of_forward_list_tag:
                                            insert_many_same_elements_into_type_info_container_at_specified_index
                                                (at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                 inline void insert_many_newly_read_into_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_insert_into_and_how facility_to_change= 
                                        static_cast<Which_type_facility_to_insert_into_and_how>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                        case Which_type_facility_to_insert_into_and_how::insert_into_vector_tag:
                                            insert_many_newly_read_elements_into_type_info_container_at_specified_index
                                                (vector_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(vector_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_insert_into_and_how::insert_into_deque_tag:
                                            insert_many_newly_read_elements_into_type_info_container_at_specified_index
                                                (deque_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(deque_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_insert_into_and_how::insert_into_map_tag:
                                            insert_many_newly_read_elements_into_type_info_container_at_specified_index
                                                (map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break; 
                                        case Which_type_facility_to_insert_into_and_how::insert_into_push_to_hash_map_tag:
                                            insert_many_newly_read_elements_into_type_info_container_at_specified_index
                                                (hash_map_containing_type_collections.at(read_from_string
                                                <Get_cont_size_type_t<decltype(hash_map_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                        case Which_type_facility_to_insert_into_and_how::insert_into_list_tag:
                                            insert_many_newly_read_elements_into_type_info_container_at_specified_index
                                                (at_for_containers_that_dont_support_it(list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;
                                        case Which_type_facility_to_insert_into_and_how::insert_into_front_of_forward_list_tag:
                                            insert_many_newly_read_elements_into_type_info_container_at_specified_index
                                                (at_for_containers_that_dont_support_it(forward_list_containing_type_collections, read_from_string
                                                <Get_cont_size_type_t<decltype(forward_list_containing_type_collections)>>
                                                (string_to_read_from, pos)), string_to_read_from, pos);
                                            break;   
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                inline void change_part_of_lists_of_collection_of_types
                                (const std::string& string_to_read_from, std::string::size_type* pos){
                                        Which_type_facility_to_change_part_of_and_how facility_to_change= 
                                        static_cast<Which_type_facility_to_change_part_of_and_how>
                                        (read_from_string<uint8_t>(string_to_read_from, pos));
                                        switch(facility_to_change){
                                            case Which_type_facility_to_change_part_of_and_how::change_array_tag_do_it_non_sequentially:
                                            change_part_of_the_container_non_sequentially
                                            (array_containing_types, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_vector_tag_do_it_non_sequentially:
                                            change_part_of_the_container_non_sequentially
                                            (vector_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_deque_tag_do_it_non_sequentially:
                                            change_part_of_the_container_non_sequentially
                                            (deque_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_map_tag_do_it_non_sequentially:
                                            change_part_of_the_container_non_sequentially
                                            (map_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_hash_map_tag_do_it_non_sequentially:
                                            change_part_of_the_container_non_sequentially
                                            (hash_map_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_list_tag_do_it_non_sequentially:
                                            change_part_of_the_container_non_sequentially
                                            (list_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_forward_list_tag_do_it_non_sequentially:
                                            change_part_of_the_container_non_sequentially
                                            (forward_list_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_array_tag_do_it_parrallely:
                                            change_part_of_the_container_parrallely_and_also_unsequentially
                                            (array_containing_types, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_vector_tag_do_it_parrallely:
                                            change_part_of_the_container_parrallely_and_also_unsequentially
                                            (vector_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_deque_tag_do_it_parrallely:
                                            change_part_of_the_container_parrallely_and_also_unsequentially
                                            (deque_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_map_tag_do_it_parrallely:
                                            change_part_of_the_container_parrallely_and_also_unsequentially
                                            (map_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_hash_map_tag_do_it_parrallely:
                                            change_part_of_the_container_parrallely_and_also_unsequentially
                                            (hash_map_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_list_tag_do_it_parrallely:
                                            change_part_of_the_container_parrallely_and_also_unsequentially
                                            (list_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            case Which_type_facility_to_change_part_of_and_how::change_forward_list_tag_do_it_parrallely:
                                            change_part_of_the_container_parrallely_and_also_unsequentially
                                            (forward_list_containing_type_collections, string_to_read_from, pos);
                                            break;
                                            default:
                                                throw std::string{"invalid type location!!!"};
                                            }
                                    }
                                    inline void push_to_list_of_collection_of_types
                                    (const std::string& string_to_read_from, std::string::size_type* pos){
                                            auto type_info= get_collections_of_types_from_string(string_to_read_from, pos);
                                            Which_type_facility_to_push_to_and_how facility_to_push_to=
                                            static_cast<Which_type_facility_to_push_to_and_how>
                                            (read_from_string<uint8_t>(string_to_read_from, pos));
                                            switch(facility_to_push_to){
                                                case Which_type_facility_to_push_to_and_how::push_to_vector_tag:
                                                    vector_containing_type_collections.push_back(type_info);
                                                    break;                                        
                                                case Which_type_facility_to_push_to_and_how::push_to_deque_tag:
                                                    deque_containing_type_collections.push_back(type_info);
                                                    break;                                    
                                                case Which_type_facility_to_push_to_and_how::push_to_map_tag:
                                                    map_containing_type_collections.push_back(type_info);
                                                    break;                                                                            
                                                case Which_type_facility_to_push_to_and_how::push_to_hash_map_tag:
                                                    hash_map_containing_type_collections.push_back(type_info);
                                                    break;                                            
                                                case Which_type_facility_to_push_to_and_how::push_to_list_tag:
                                                    list_containing_type_collections.push_back(type_info);
                                                    break;                                    
                                                case Which_type_facility_to_push_to_and_how::push_to_front_of_forward_list_tag:
                                                    forward_list_containing_type_collections.push_front(type_info);
                                                    break;                                    
                                                default:
                                                    throw std::string{"invalid type location!!!"};
                                                }
                                            }
                                    inline void push_same_many_to_list_of_collection_of_types
                                    (const std::string& string_to_read_from, std::string::size_type* pos){
                                            Which_type_facility_to_push_to_and_how facility_to_push_to=
                                            static_cast<Which_type_facility_to_push_to_and_how>
                                            (read_from_string<uint8_t>(string_to_read_from, pos));
                                            switch(facility_to_push_to){
                                                case Which_type_facility_to_push_to_and_how::push_to_vector_tag:
                                                    push_same_newly_read_many_times
                                                    (vector_containing_type_collections, string_to_read_from, pos);
                                                    break;                                        
                                                case Which_type_facility_to_push_to_and_how::push_to_deque_tag:
                                                    push_same_newly_read_many_times
                                                    (deque_containing_type_collections, string_to_read_from, pos);
                                                    break;                                    
                                                case Which_type_facility_to_push_to_and_how::push_to_map_tag:
                                                    push_same_newly_read_many_times
                                                    (map_containing_type_collections, string_to_read_from, pos);
                                                    break;                                                                            
                                                case Which_type_facility_to_push_to_and_how::push_to_hash_map_tag:
                                                    push_same_newly_read_many_times
                                                    (hash_map_containing_type_collections, string_to_read_from, pos);
                                                    break;                                            
                                                case Which_type_facility_to_push_to_and_how::push_to_list_tag:
                                                    push_same_newly_read_many_times
                                                    (list_containing_type_collections, string_to_read_from, pos);
                                                    break;                                    
                                                case Which_type_facility_to_push_to_and_how::push_to_front_of_forward_list_tag:
                                                    push_same_newly_read_at_front_many_times
                                                    (forward_list_containing_type_collections, string_to_read_from, pos);
                                                    break;                                    
                                                default:
                                                    throw std::string{"invalid type location!!!"};
                                                }
                                            }
                                    inline void push_many_newly_read_to_list_of_collection_of_types
                                    (const std::string& string_to_read_from, std::string::size_type* pos){
                                            Which_type_facility_to_push_to_and_how facility_to_push_to=
                                            static_cast<Which_type_facility_to_push_to_and_how>
                                            (read_from_string<uint8_t>(string_to_read_from, pos));
                                            switch(facility_to_push_to){
                                                case Which_type_facility_to_push_to_and_how::push_to_vector_tag:
                                                    push_newly_read_many_times
                                                    (vector_containing_type_collections, string_to_read_from, pos);
                                                    break;                                        
                                                case Which_type_facility_to_push_to_and_how::push_to_deque_tag:
                                                    push_newly_read_many_times
                                                    (deque_containing_type_collections, string_to_read_from, pos);
                                                    break;                                    
                                                case Which_type_facility_to_push_to_and_how::push_to_map_tag:
                                                    push_newly_read_many_times
                                                    (map_containing_type_collections, string_to_read_from, pos);
                                                    break;                                                                            
                                                case Which_type_facility_to_push_to_and_how::push_to_hash_map_tag:
                                                    push_newly_read_many_times
                                                    (hash_map_containing_type_collections, string_to_read_from, pos);
                                                    break;                                            
                                                case Which_type_facility_to_push_to_and_how::push_to_list_tag:
                                                    push_newly_read_many_times
                                                    (list_containing_type_collections, string_to_read_from, pos);
                                                    break;                                    
                                                case Which_type_facility_to_push_to_and_how::push_to_front_of_forward_list_tag:
                                                    push_newly_read_at_front_many_times
                                                    (forward_list_containing_type_collections, string_to_read_from, pos);
                                                    break;                                    
                                                default:
                                                    throw std::string{"invalid type location!!!"};
                                                }
                                            }
                                    inline void pop_from_list_of_collection_of_types
                                    (const std::string& string_to_read_from, std::string::size_type* pos){
                                            Which_type_facility_to_pop facility_to_pop_from= 
                                            static_cast<Which_type_facility_to_pop>
                                            (read_from_string<uint8_t>(string_to_read_from, pos));
                                            switch(facility_to_pop_from){
                                                case Which_type_facility_to_pop::pop_from_vector_tag:                                  
                                                    pop_back_container(vector_containing_type_collections);
                                                    break;
                                                case Which_type_facility_to_pop::pop_from_deque_tag:  
                                                    pop_back_container(deque_containing_type_collections);
                                                    break;
                                                case Which_type_facility_to_pop::pop_from_map_tag:                                       
                                                    pop_back_container(map_containing_type_collections);
                                                    break;                                          
                                                case Which_type_facility_to_pop::pop_from_hash_map_tag:                                        
                                                    pop_back_container(hash_map_containing_type_collections);
                                                    break;                                           
                                                 case Which_type_facility_to_pop::pop_from_list_tag:
                                                    pop_back_container(list_containing_type_collections);
                                                    break;                                    
                                                case Which_type_facility_to_pop::pop_from_front_of_forward_list_tag:
                                                    pop_front_from_forward_list(forward_list_containing_type_collections);
                                                    break;                                        
                                                default:
                                                    throw std::string{"invalid type location!!!"};
                                                }
                                            }
                                    inline void pop_many_from_list_of_collection_of_types
                                    (const std::string& string_to_read_from, std::string::size_type* pos){
                                            Which_type_facility_to_pop facility_to_pop_from= 
                                            static_cast<Which_type_facility_to_pop>
                                            (read_from_string<uint8_t>(string_to_read_from, pos));
                                            switch(facility_to_pop_from){
                                                case Which_type_facility_to_pop::pop_from_vector_tag:                                  
                                                    pop_back_container_many_times(vector_containing_type_collections, string_to_read_from, pos);
                                                    break;
                                                case Which_type_facility_to_pop::pop_from_deque_tag:  
                                                    pop_back_container_many_times(deque_containing_type_collections, string_to_read_from, pos);
                                                    break;
                                                case Which_type_facility_to_pop::pop_from_map_tag:                                       
                                                    pop_back_container_many_times(map_containing_type_collections, string_to_read_from, pos);
                                                    break;                                          
                                                case Which_type_facility_to_pop::pop_from_hash_map_tag:                                        
                                                    pop_back_container_many_times(hash_map_containing_type_collections, string_to_read_from, pos);
                                                    break;                                           
                                                 case Which_type_facility_to_pop::pop_from_list_tag:
                                                    pop_back_container_many_times(list_containing_type_collections, string_to_read_from, pos);
                                                    break;                                    
                                                case Which_type_facility_to_pop::pop_from_front_of_forward_list_tag:
                                                    pop_front_container_of_forward_list_many_times(forward_list_containing_type_collections, string_to_read_from, pos);
                                                    break;                                        
                                                default:
                                                    throw std::string{"invalid type location!!!"};
                                                }
                                            }
                                        template<typename Container_t>
                                        using Iterator_subscript_index_t=Iterator_subscript_index_t<Container_t>;
                                        inline void insert_into_list_of_collection_of_types
                                        (const std::string& string_to_read_from, std::string::size_type* pos){
                                                auto type_info= get_collections_of_types_from_string(string_to_read_from, pos);
                                                Which_type_facility_to_insert_into_and_how facility_to_insert_into= 
                                                static_cast<Which_type_facility_to_insert_into_and_how>
                                                (read_from_string<uint8_t>(string_to_read_from, pos));
                                                switch(facility_to_insert_into){
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_vector_tag:
                                                        vector_containing_type_collections.insert
                                                        (std::next(vector_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(vector_containing_type_collections)>>
                                                        (string_to_read_from, pos)), type_info);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_deque_tag:
                                                        deque_containing_type_collections.insert
                                                        (std::next(deque_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(deque_containing_type_collections)>>
                                                        (string_to_read_from, pos)),  type_info);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_map_tag:
                                                        map_containing_type_collections.insert
                                                        (std::next(map_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(map_containing_type_collections)>>
                                                        (string_to_read_from, pos)),  type_info);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_push_to_hash_map_tag:
                                                        hash_map_containing_type_collections.insert
                                                        (std::next(hash_map_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(hash_map_containing_type_collections)>>
                                                        (string_to_read_from, pos)),  type_info);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_list_tag:
                                                        list_containing_type_collections.insert
                                                        (std::next(list_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(list_containing_type_collections)>>
                                                        (string_to_read_from, pos)),  type_info);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_front_of_forward_list_tag:
                                                        forward_list_containing_type_collections.insert_after
                                                        (std::next(forward_list_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(forward_list_containing_type_collections)>>
                                                        (string_to_read_from, pos)),  type_info);
                                                        break;                                                   
                                                    default:
                                                        throw std::string{"invalid type location!!!"};
                                                }
                                            }
                                    inline void insert_same_many_into_list_of_collection_of_types
                                    (const std::string& string_to_read_from, std::string::size_type* pos){
                                                Which_type_facility_to_insert_into_and_how facility_to_insert_into= 
                                                static_cast<Which_type_facility_to_insert_into_and_how>
                                                (read_from_string<uint8_t>(string_to_read_from, pos));
                                                switch(facility_to_insert_into){
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_vector_tag:
                                                        insert_same_newly_read_many_times_at_specified_index
                                                        (vector_containing_type_collections, string_to_read_from, pos);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_deque_tag:
                                                        insert_same_newly_read_many_times_at_specified_index
                                                        (deque_containing_type_collections, string_to_read_from, pos);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_map_tag:
                                                        insert_same_newly_read_many_times_at_specified_index
                                                        (map_containing_type_collections, string_to_read_from, pos);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_push_to_hash_map_tag:
                                                        insert_same_newly_read_many_times_at_specified_index
                                                        (hash_map_containing_type_collections, string_to_read_from, pos);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_list_tag:
                                                        insert_same_newly_read_many_times_at_specified_index
                                                        (list_containing_type_collections, string_to_read_from, pos);
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_front_of_forward_list_tag:
                                                        insert_same_newly_read_many_times_at_specified_index_forward_list
                                                        (forward_list_containing_type_collections, string_to_read_from, pos);
                                                        break;                                                   
                                                    default:
                                                        throw std::string{"invalid type location!!!"};
                                                }
                                            }
                                    inline void insert_many_newly_read_into_list_of_collection_of_types
                                    (const std::string& string_to_read_from, std::string::size_type* pos){
                                                auto type_info= get_list_of_collections_of_types_from_string_the_list_can_be_of_any_container_type<std::vector>(string_to_read_from, pos);
                                                Which_type_facility_to_insert_into_and_how facility_to_insert_into= 
                                                static_cast<Which_type_facility_to_insert_into_and_how>
                                                (read_from_string<uint8_t>(string_to_read_from, pos));
                                                switch(facility_to_insert_into){
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_vector_tag:
                                                        vector_containing_type_collections.insert
                                                        (std::next(vector_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(vector_containing_type_collections)>>
                                                        (string_to_read_from, pos)), type_info.begin(), type_info.end());
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_deque_tag:
                                                        deque_containing_type_collections.insert
                                                        (std::next(deque_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(deque_containing_type_collections)>>
                                                        (string_to_read_from, pos)), type_info.begin(), type_info.end());
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_map_tag:
                                                        map_containing_type_collections.insert
                                                        (std::next(map_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(map_containing_type_collections)>>
                                                        (string_to_read_from, pos)), type_info.begin(), type_info.end());
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_push_to_hash_map_tag:
                                                        hash_map_containing_type_collections.insert
                                                        (std::next(hash_map_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(hash_map_containing_type_collections)>>
                                                        (string_to_read_from, pos)), type_info.begin(), type_info.end());
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_list_tag:
                                                        list_containing_type_collections.insert
                                                        (std::next(list_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(list_containing_type_collections)>>
                                                        (string_to_read_from, pos)), type_info.begin(), type_info.end());
                                                        break;
                                                    case Which_type_facility_to_insert_into_and_how::insert_into_front_of_forward_list_tag:
                                                        forward_list_containing_type_collections.insert_after
                                                        (std::next(forward_list_containing_type_collections.begin(),
                                                        read_from_string<Iterator_subscript_index_t<decltype(forward_list_containing_type_collections)>>
                                                        (string_to_read_from, pos)), type_info.begin(), type_info.end());
                                                        break;                                                   
                                                    default:
                                                        throw std::string{"invalid type location!!!"};
                                                }
                                            }


                            }    
                        }    

                    }
                }
```


            namespace polymorphic_extensible_engine{
            namespace implementation_of_the_interface_used_by_macro{
            namespace scalar_to_scalar{
                template<typename T>
                concept Polymorphic_object = requires(Lhs_t a){
                    {Lhs_t.ptr}->std::same_as<void>;
                    {Lhs_t.tag}->std::same_as<Type_tag>;
                };
                template<typename Lhs_t, bool op_action_type>
                struct const_qualified_if_false{
                using type= Lhs_t;
                }
                template<typename Lhs_t>
                struct const_qualified_if_false<false>{
                using type= const Lhs_t;
                }
                template<typename Lhs_t>
                using const_qualified_if_false_t = const_qualified_if_false<Lhs_t>::type;
                template<typename Op, bool op_action_type, std::is_arithmetic Lhs_t>
                    inline typename std::conditional<op_action_type == true, void, bool>
                    all_ops(const_qualified_if_false_t<op_action_type, Lhs_t>* lhs,const std::string& rhs) {
                        if constexpr (op_action_type == true) {
                            if constexpr (std::is_same_v<Op, std::plus>){
                                *lhs = Op{}(std::to_string(*lhs), std::cref(rhs)); 
                            }
                            else{
                                throw std::string{"attempt to do an operation other than plus while right hand side operand is string but left hand side isnt"};
                            }
                        }
                        else {
                            *lhs = Op{}(std::to_string(*lhs), std::cref(rhs)); 
                        }
                }
                template<typename Op, bool op_action_type, absolute_base::Is_String_Or_Numeric Lhs_t,std::is_arithmetic Rhs_t>
                    inline typename std::conditional<op_action_type == true, void, bool>
                    all_ops(const_qualified_if_false_t<op_action_type, std::string>* lhs,const Rhs_t& rhs) {
                        //Everything will naturally use this!
                        if constexpr (op_action_type == true) {
                            if constexpr (std::is_same_v<Op, std::plus>){
                                *lhs = Op{}(std::ref(*lhs), std::to_string(rhs)); 
                            }
                            else{
                                throw std::string{"attempt to do an operation other than plus while left hand side operand is string but right hand side isnt"};
                            }
                        }
                        else {
                            return Op{}(std::cref(*Lhs_t), std::to_string(rhs));;
                        }
                    }
                template<typename Op, bool op_action_type, absolute_base::Is_String_Or_Numeric Lhs_t,absolute_base::Is_String_Or_Numeric Rhs_t>
                    inline typename std::conditional<op_action_type == true, void, bool>
                    all_ops(const_qualified_if_false_t<op_action_type, Lhs_t>* lhs,const Rhs_t& rhs) {
                        //Everything will naturally use this!
                        if constexpr (op_action_type == true) {
                            *lhs = Op{}(std::ref(*lhs), std::cref(rhs)); 
                        }
                        else {
                            return Op{}(std::cref(*Lhs_t), std::cref(rhs));;
                        }
                    }
                template<typename Op, bool op_action_type, typename Lhs_t,typename Rhs_t>
                    inline typename std::conditional<op_action_type == true, void, bool>
                    all_ops(const_qualified_if_false_t<op_action_type, Lhs_t>* lhs,const Rhs_t& rhs) {
                        op_generator(lhs, rhs)
                    }

    
                };
                 
    
                
                     
                template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
                inline typename std::conditional<op_action_type == true, void, bool>  
                    op_scalar_or_collection_with_collection(const_qualified_if_false_t<op_action_type, Lhs_t>* lhs,const Rhs_t& rhs){
                        return all_ops<Op, op_action_type, Lhs_t, Rhs_t>(lhs, rhs);
                }
    
    
                
                template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
                requires{//the concept is weather the expression below works or not
                typename std::derived_from
                <std::iterator_traits<Lhs_t::underlying_container::iterator>::iterator_category, std::input_iterator_tag>;
                }
                inline typename std::conditional<op_action_type == true, void, bool>  
                    op_scalar_or_collection_with_collection(const_qualified_if_false_t<op_action_type, Lhs_t>* lhs,const Rhs_t& rhs){
                        switch(lhs->execution_policy){
                            case Thread_policy_t::single_thread_exec:
                                std::for_each(std::execution::unseq , lhs->begin(), lhs->end(),
                                    [](const auto& lhs_sub_element){
                                         return all_ops<Op, op_action_type, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs);
                                });
                            case Thread_policy_t::unsequenced_parrallel_exec:
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
                    op_scalar_or_collection_with_collection(const_qualified_if_false_t<op_action_type, Lhs_t>* lhs,const Rhs_t& rhs){
                        switch(lhs->execution_policy){
                            case Thread_policy_t::single_thread_exec:
                                std::for_each(std::execution::unseq , lhs->begin()+indexes_to_skip, lhs->end(),
                                    [](const auto& lhs_sub_element){
                                         return all_ops<Op, op_action_type, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs);
                                });
                            case Thread_policy_t::unsequenced_parrallel_exec:
                                std::for_each(std::execution::par_unseq , lhs->begin()+indexes_to_skip, lhs->end(),
                                    [](const auto& lhs_sub_element){
                                        return all_ops<Op, op_action_type, Lhs_t::value_type,Rhs_t>(lhs_sub_element,rhs);
                                });
                        }
    
                        }
    
                template<typename Op, bool op_action_type, typename Lhs_t, typename Rhs_t>
                requires{
                    std::derived_from(Nested_type_info, Lhs_t); //requiresment is 
                    //just to make clear that Lhs_t is Nested_type_info, while keeping the interface uniform 
                }
                inline typename std::conditional<op_action_type == true, void, bool> 
                     
                    op_scalar_or_collection_with_collection(const_qualified_if_false_t<op_action_type, Lhs_t>* lhs,const Rhs_t& rhs){
                
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
                        op_potential_scalar_with_collection(const_qualified_if_false_t<op_action_type, Lhs_t>* lhs,const Rhs_t& rhs){
                        auto& formated_rhs= *(rhs->ptr);
                            switch(rhs.execution_policy){
                                case Thread_policy_t::single_thread_exec:
                                    std::for_each(std::execution::unseq, formated_rhs->begin(), formated_rhs->end(),
                                        [](const auto& rhs_sub_element){
                                            return op_scalar_or_collection_with_collection<Op, op_action_type, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element);
                                    });
                                case Thread_policy_t::unsequenced_parrallel_exec:
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
                        op_potential_scalar_with_collection(const_qualified_if_false_t<op_action_type, Lhs_t>* lhs,const Rhs_t& rhs){
                        auto& formated_rhs= *(rhs->ptr);
                            switch(rhs.execution_policy){
                                case Thread_policy_t::single_thread_exec:
                                    std::for_each(std::execution::unseq, formated_rhs->begin()+indexes_to_skip, formated_rhs->end(),
                                        [](const auto& rhs_sub_element){
                                            return op_scalar_or_collection_with_collection<Op, op_action_type, Lhs_t,Rhs_t::value_type>(lhs,rhs_sub_element);
                                    });
                                case Thread_policy_t::unsequenced_parrallel_exec:
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
                     requires{

                     }
                    interface_of_all_operations_on_potential_scaler_with_potential_scalar(const Polymoprhic_extensible_engine first_obj, const Polymoprhic_extensible_engine second_obj) {
                    const_qualified_if_false_t<op_action_type, Lhs_t>* formated_lhs= static_cast<const_qualified_if_false_t<op_action_type, Lhs_t>*>(first_obj->ptr);
                    Rhs_t* formated_rhs= static_cast<Rhs_t*>(second_obj->ptr);
                    implementation_of_the_interface_used_by_macro::op_potential_scalar_with_collection<Op, op_action_type>(formated_lhs, formated_rhs);
                    }
                    template<typename Op, bool op_action_type,typename Lhs_t, typename Rhs_t>
                    inline inline typename std::conditional<op_action_type == true, void, bool>  
                     requires{

                     }
                    interface_of_all_ops_scalar_to_scalar(const Polymoprhic_extensible_engine first_obj, const Polymoprhic_extensible_engine second_obj) {
                    const_qualified_if_false_t<op_action_type, Lhs_t>* formated_lhs= static_cast<const_qualified_if_false_t<op_action_type, Lhs_t>*>(first_obj->ptr);
                    Rhs_t* formated_rhs= static_cast<Rhs_t*>(second_obj->ptr);
                    implementation_of_the_interface_used_by_macro::all_ops<Op, op_action_type>(formated_lhs, formated_rhs);
                    }
                    template<typename Op, bool op_action_type,typename Lhs_t, typename Rhs_t>
                    inline inline typename std::conditional<op_action_type == true, void, bool>  
                     requires{
                         std::derived_from(Nested_type_info, Rhs_t); //requiresment is 
                         //just to make clear that Rhs_t is Nested_type_info, while keeping the interface uniform 
                     }
                    interface_of_all_operations_on_potential_scaler_with_collections_of_polymorphic_engine_objects(const Polymoprhic_extensible_engine first_obj, const Polymoprhic_extensible_engine second_obj) {
                    const_qualified_if_false_t<op_action_type, Lhs_t>* formated_lhs= static_cast<const_qualified_if_false_t<op_action_type, Lhs_t>*>(first_obj->ptr);
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
                    underlying_container_specialization_and_thread_execution_policy& destination_data= 
                    *(new underlying_container_specialization_and_thread_execution_policy
                    (source->execution_policy, 0));
                    switch(source->execution_policy){
                    case Thread_policy_t::single_thread_exec:
                        std::for_each(std::execution::unseq , formated_source.ptr.begin(), formated_source.ptr.end(),
                            [&destination_data](const Polymoprhic_extensible_engine source_ptr){
                                destination_data.ptr.push_back(Polymoprhic_extensible_engine(source_ptr));
                        });
                    case Thread_policy_t::unsequenced_parrallel_exec:
                        destination_data.ptr.reserve(formated_source);
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
                     std::size_t formated_size= *(static_cast<uintptr_t*>(formated_source[monolithic_buffer_resource_index].ptr));
                    using memory_region=std::pmr::monotonic_buffer_resource::monotonic_buffer_resource;
                    memory_region* buffer= new memory_region(formated_size);
                    std::pmr::polymorphic_allocator<std::byte> allocator_used{buffer};
                    underlying_container_specialization& destination_data= *(allocator_used.new_object<underlying_container_specialization_and_thread_execution_policy>(source->execution_policy,formated_source.size()));
                    destination_data[monolithic_buffer_resource_index] = {monolithic_buffer_resource_tag, static_cast<void*>(buffer)};
                    destination_data[all_elements_size_uintptr_t_index]= {all_elements_size_uintptr_t_tag,static_cast<void*>(allocator_used.new_object< std::size_t>(formated_size))};
                    switch(source->execution_policy){
                    case Thread_policy_t::single_thread_exec:
                        std::copy(std::execution::unseq , formated_source.ptr.begin()+indexes_to_skip, formated_source.ptr.end(), destination_data.ptr.begin()+indexes_to_skip, 
                            [](const Polymoprhic_extensible_engine source_ptr){
                                return Polymoprhic_extensible_engine(source_ptr, allocator_used);
                        });
                    case Thread_policy_t::unsequenced_parrallel_exec:
                        std::copy(std::execution::par_unseq , formated_source.ptr.begin()+indexes_to_skip, formated_source.ptr.end(), destination_data.ptr.begin()+indexes_to_skip, 
                            [](const Polymoprhic_extensible_engine source_ptr){
                                return Polymoprhic_extensible_engine(source_ptr, allocator_used);
                        });
                    }
                    return static_cast<void*>(allocator_used.new_object<Nested_type_info>(tag, source->execution_policy, static_cast<void*>(&destination_data))); 

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
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::vector_containing_type_collections>(underlying_obj);
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
                                ptr = copy_nested<Source_and_target_type, Type_tag_for_input::vector_containing_type_collections>(underlying_obj);
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
                static inline void* make_nested(const std::string& string_to_read_from, std::string::size_type* pos){
                    auto thread_policy = static_cast<thread_policy>
                    (read_from_string<uint8_t>(string_to_read_from, pos_size));
                    underlying_container_specialization& underlying_data= 
                    *(new underlying_container_specialization_and_thread_execution_policy(thread_policy,0));

                    switch(thread_policy){
                    case Thread_policy_t::single_thread_exec:
                        for(int i =0; i< size_reserve_for_the_container; i++){
                            underlying_data.ptr.push_back(Polymoprhic_extensible_engine
                            {string_to_read_from, pos,static_cast<Type_tag_for_input>(read_from_string<uint8_t>
                            (string_to_read_from, pos_size))});
                        }
                    case Thread_policy_t::unsequenced_parrallel_exec:
                        {
                            destination_data.ptr.reserve(read_from_string< std::size_t>(string_to_read_from, pos));
                            std::generate(std::execution::par_unseq , underlying_data.ptr.begin(), underlying_data.ptr.end(), 
                                [&string_to_read_from, &pos](){
                                    return Polymoprhic_extensible_engine
                                    {string_to_read_from, pos,
                                    static_cast<Type_tag_for_input>(read_from_string<uint8_t>
                                        (string_to_read_from, pos_size))};
                            });
                    }
                    return static_cast<void*>(allocator_used.new_object<Nested_type_info>(
                        static_cast<Type_tag_for_input>(
                        read_from_string<uint8_t>(string_to_read_from, pos_size)),
                        thread_policy,
                        static_cast<void*>(&underlying_data)                                
                    )); 
                }

            template<typename Underlying_container_specialization, Type_tag_for_input tag>
            requires{//the concept is weather the expression below works or not
            typename std::derived_from
                <std::iterator_traits<Underlying_container_specialization::underlying_container::iterator>::iterator_category, std::random_access_iterator_tag>;
            }
                static inline void*  make_nested(const std::string& string_to_read_from, std::string::size_type* pos){
                    auto thread_policy = static_cast<thread_policy>
                    (read_from_string<uint8_t>(string_to_read_from, pos_size));
                    auto type_info_needed=main_interface_to_get_type_information::get_type_info_from_the_specified_storage_facility(string_to_read_from, pos);
                    auto   size_reserve_for_the_elements= type_info_needed.type_info_of_all.size();
                    auto   size_reserve_for_the_container= type_info_needed.size_of_all;
                    auto  total_ size_reserve=  size_reserve_for_the_elements+
                    size_reserve_for_the_container+extra_size_reserve_in_monolithic_buffer<Polymoprhic_extensible_engine>;
                    using memory_region=std::pmr::monotonic_buffer_resource::monotonic_buffer_resource;
                    memory_region* buffer= new memory_region(total_size_reserve);
                    std::pmr::polymorphic_allocator<std::byte> allocator_used{buffer};
                    underlying_container_specialization& underlying_data= 
                    *(allocator_used.new_object<underlying_container_specialization_and_thread_execution_policy>
                    (thread_policy, size_reserve_for_the_container));
                    underlying_data[monolithic_buffer_resource_index] = {monolithic_buffer_resource_tag, static_cast<void*>(buffer)};
                    underlying_data[all_elements_size_uintptr_t_index]= {all_elements_size_uintptr_t_tag,static_cast<void*>(allocator_used.new_object< std::size_t>(final_size))};
                    Get_cont_size_type_t<std::vector<Type_Tag>> index;

                    switch(thread_policy){
                    case Thread_policy_t::single_thread_exec:
                        {
                        std::generate(std::execution::unseq , underlying_data.ptr.begin(), underlying_data.ptr.end(), 
                            [&string_to_read_from, &pos, &index, &type_collection=type_info_needed.type_info_of_all, &allocator_used](){
                                return Polymoprhic_extensible_engine{string_to_read_from, pos,type_collection[index++], allocator_used};
                        });
                        }
                    case Thread_policy_t::unsequenced_parrallel_exec:
                        std::generate(std::execution::par_unseq , underlying_data.ptr.begin(), underlying_data.ptr.end(), 
                            [&string_to_read_from, &pos, &index, &type_collection=type_info_needed.type_info_of_all, &allocator_used](){
                                return Polymoprhic_extensible_engine{string_to_read_from, pos,type_collection[index++], allocator_used};
                        });
                    }
                    return static_cast<void*>(allocator_used.new_object<Nested_type_info>(
                        static_cast<Type_tag_for_input>(
                        read_from_string<uint8_t>(string_to_read_from, pos_size)),
                        thread_policy,
                        static_cast<void*>(&underlying_data)                                
                    )); 

                }
            inline  Polymoprhic_extensible_engine
            (const std::string& string_to_read_from, std::string::size_type* pos_size,Type_tag tag_arg){
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
                                (allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
                                <underlying_container::value_type:value_type>
                                (string_to_read_from, pos_size)
                                );
                            tag= tag_arg;
                        }                    
                    case Type_tag::vector_uintptr: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<uintptr_t>>;
                            ptr= static_cast<void*>
                                (allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
                                <underlying_container::value_type:value_type>
                                (string_to_read_from, pos_size)
                                );
                            tag= tag_arg;
                        }                    
                    case Type_tag::vector_intptr: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<intptr_t>>;
                            ptr= static_cast<void*>
                                (allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
                                <underlying_container::value_type:value_type>
                                (string_to_read_from, pos_size)
                                );
                            tag= tag_arg;
                        }                                    
                    case Type_tag::vector_long_double_tag_implementation_defined_size: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<long double>>;
                            ptr= static_cast<void*>
                                (allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
                                <underlying_container::value_type:value_type>
                                (string_to_read_from, pos_size)
                                );
                            tag= tag_arg;
                        }                                 
                    case Type_tag::nested_type_with_dynamic_container: 
                        {
                            Type_tag_for_input underlying_nested_type_tag= static_cast<Type_tag_for_input>(read_from_string<uint8_t>(string_to_read_from, pos_size));
                            switch(underlying_nested_type_tag){
                                case Type_tag_for_input::array_nested_type_vector:{
                                    using Source_and_target_type= No_tag_template_type_info<std::vector<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::vector_containing_type_collections>(underlying_obj, string_to_read_from, pos_size);
                                    break;
                                    }
                                case Type_tag_for_input::array_nested_type_deque:{
                                    using Source_and_target_type= No_tag_template_type_info<std::deque<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::type_in_deque_tag>(underlying_obj, string_to_read_from, pos_size);
                                    break;}
                                case Type_tag_for_input::array_nested_type_list:{
                                    using Source_and_target_type= No_tag_template_type_info<std::list<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::type_in_list>(underlying_obj, string_to_read_from, pos_size);
                                    break;}
                                case Type_tag_for_input::array_nested_type_forward_list:{
                                    using Source_and_target_type= No_tag_template_type_info<std::forward_list<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::type_in_forward_list>(underlying_obj, string_to_read_from, pos_size);
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
            template<absolute_base::Is_String_Or_Numeric T>
            static inline No_tag_template_type_info<std::vector<T>>*
            allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
            (const std::string& string_to_read_from,std::string: std::size_type* pos_size, 
            std::pmr::polymorphic_allocator<std::byte> allocator_used){
                auto *vec = allocator_used.new_object<No_tag_template_type_info<std::vector<T>>>
                (read_from_string< std::size_t>(string_to_read_from, pos_size));
                std::generate(vec->begin(), vec->end(),
                    [&string_to_read_from, &pos](){
                        return read_from_string<T>
                        (string_to_read_from, pos_size);
                    })
                return vec;
            } 
            template<absolute_base::Is_String_Or_Numeric T>
            static inline No_tag_template_type_info<std::vector<T>>*
            allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
            (const std::string& string_to_read_from,std::string: std::size_type* pos_size){
                auto *vec = new No_tag_template_type_info<std::vector<T>(read_from_string< std::size_t>
                (string_to_read_from, pos_size));
                std::generate(vec->begin(), vec->end(),
                    [&string_to_read_from, &pos](){
                        return read_from_string<T>
                        (string_to_read_from, pos_size);
                    })
                return vec;
            } 
            inline  Polymoprhic_extensible_engine
            (const std::string& string_to_read_from, std::string::size_type* pos_size,Type_tag tag_arg,
            std::pmr::polymorphic_allocator<std::byte> allocator_used){
                switch(tag_arg){
                    //to be completed
                    case Type_tag::string_tag_for_15_plus_operand_ops: 
                        {
                            using underlying_type_of_ptr= std::string;
                            ptr= static_cast<void*>
                                (allocator_used.new_object<underlying_type_of_ptr>(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }
                    case Type_tag::uintptr_tag_for_15_plus_operand_ops: 
                        {
                            using underlying_type_of_ptr= uintptr_t;
                            ptr= static_cast<void*>
                                (allocator_used.new_object<underlying_type_of_ptr>(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }
                    case Type_tag::intptr_tag_for_15_plus_operand_ops: 
                        {
                            using underlying_type_of_ptr= intptr_t;
                            ptr= static_cast<void*>
                                (allocator_used.new_object<underlying_type_of_ptr>(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::long_double_tag_implementation_defined_size_for_15_plus_operand_ops: 
                        {
                            using underlying_type_of_ptr= long double;
                            ptr= static_cast<void*>
                                (allocator_used.new_object<underlying_type_of_ptr>(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::long_double_tag_implementation_defined_size: 
                        {
                            using underlying_type_of_ptr= long double;
                            ptr= static_cast<void*>
                                (allocator_used.new_object<underlying_type_of_ptr>(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::uintptr_tag: 
                        {
                            using underlying_type_of_ptr= uintptr_t;
                            ptr= static_cast<void*>
                                (allocator_used.new_object<underlying_type_of_ptr>(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::string_tag: 
                        {
                            using underlying_type_of_ptr= std::string;
                            ptr= static_cast<void*>
                                (allocator_used.new_object<underlying_type_of_ptr>(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::intptr_tag: 
                        {
                            using underlying_type_of_ptr= uintptr_t;
                            ptr= static_cast<void*>
                                (allocator_used.new_object<underlying_type_of_ptr>(read_from_string<underlying_type_of_ptr>(string_to_read_from, pos_size)));
                            tag= tag_arg;
                        }                    
                    case Type_tag::vector_string: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<std::string>>;
                            ptr= static_cast<void*>
                                (allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
                                <underlying_container::value_type:value_type>
                                (string_to_read_from, pos_size,allocator_used)
                                );
                            tag= tag_arg;
                        }                    
                    case Type_tag::vector_uintptr: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<uintptr_t>>;
                            ptr= static_cast<void*>
                                (allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
                                <underlying_container::value_type:value_type>
                                (string_to_read_from, pos_size,allocator_used)
                                );
                            tag= tag_arg;
                        }                    
                    case Type_tag::vector_intptr: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<intptr_t>>;
                            ptr= static_cast<void*>
                                (allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
                                <underlying_container::value_type:value_type>
                                (string_to_read_from, pos_size,allocator_used)
                                );
                            tag= tag_arg;
                        }                                    
                    case Type_tag::vector_long_double_tag_implementation_defined_size: 
                        {
                            using underlying_type_of_ptr= No_tag_template_type_info<std::vector<long double>>;
                            ptr= static_cast<void*>
                                (allocate_and_return_vector_of_any_type_packed_in_No_tag_template_type_info_type
                                <underlying_container::value_type:value_type>
                                (string_to_read_from, pos_size,allocator_used)
                                );
                            tag= tag_arg;
                        }                                 
                    case Type_tag::nested_type_with_dynamic_container: 
                        {
                            Type_tag_for_input underlying_nested_type_tag= static_cast<Type_tag_for_input>(read_from_string<uint8_t>(string_to_read_from, pos_size));
                            switch(underlying_nested_type_tag){
                                case Type_tag_for_input::array_nested_type_vector:{
                                    using Source_and_target_type= No_tag_template_type_info<std::vector<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::vector_containing_type_collections>(underlying_obj, string_to_read_from, pos_size);
                                    break;
                                    }
                                case Type_tag_for_input::array_nested_type_deque:{
                                    using Source_and_target_type= No_tag_template_type_info<std::deque<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::type_in_deque_tag>(underlying_obj, string_to_read_from, pos_size);
                                    break;}
                                case Type_tag_for_input::array_nested_type_list:{
                                    using Source_and_target_type= No_tag_template_type_info<std::list<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::type_in_list>(underlying_obj, string_to_read_from, pos_size);
                                    break;}
                                case Type_tag_for_input::array_nested_type_forward_list:{
                                    using Source_and_target_type= No_tag_template_type_info<std::forward_list<Polymoprhic_extensible_engine>>;
                                    tag= Type_tag::nested_type_with_dynamic_container;
                                    ptr = make_nested<Source_and_target_type, Type_tag_for_input::type_in_forward_list>(underlying_obj, string_to_read_from, pos_size);
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
            requires{
            typename std::derived_from
                <std::iterator_traits<Underlying_container_specialization::underlying_container::iterator>::iterator_category, std::random_access_iterator_tag>;
            }
            inline void destruct_sequence_using_the_globally_specified_indexes_to_skip_variable(const Underlying_container_specialization& sequence_with_policy){
                const auto* container= sequence_with_policy.ptr;
                switch(sequence_with_policy->execution_policy){
                    case Thread_policy_t::single_thread_exec:
                        std::for_each(std::execution::unseq, container->begin()+indexes_to_skip, container->end(), 
                        [](const Polymoprhic_extensible_engine source_ptr){
                            source_ptr.~Polymoprhic_extensible_engine();
                        });
                    case Thread_policy_t::unsequenced_parrallel_exec:
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
                            case Type_tag_for_input::vector_containing_type_collections: {
                                using underlying_container_specialization_and_thread_execution_policy = No_tag_template_type_info<std::vector<Polymoprhic_extensible_engine>>;
                                const underlying_container_specialization_and_thread_execution_policy& sequence_with_policy = 
                                *(static_cast<underlying_container_specialization_and_thread_execution_policy*>(underlying_obj->ptr));
                                destruct_sequence_using_the_globally_specified_indexes_to_skip_variable(sequence_with_policy);
                                ~((sequence_with_policy->ptr)[monolithic_buffer_resource_index])();
                                break;
                            }
                            case Type_tag_for_input::type_in_deque_tag: {
                                using underlying_container_specialization_and_thread_execution_policy = No_tag_template_type_info<std::deque<Polymoprhic_extensible_engine>>;
                                const underlying_container_specialization_and_thread_execution_policy& sequence_with_policy = 
                                *(static_cast<underlying_container_specialization_and_thread_execution_policy*>(underlying_obj->ptr));
                                destruct_sequence_using_the_globally_specified_indexes_to_skip_variable(sequence_with_policy);
                                ~((sequence_with_policy->ptr)[monolithic_buffer_resource_index])();                                break;
                            }
                            case Type_tag_for_input::type_in_list: {
                                using underlying_container_specialization_and_thread_execution_policy = No_tag_template_type_info<std::list<Polymoprhic_extensible_engine>>;
                                delete (static_cast<underlying_container_specialization_and_thread_execution_policy*>(underlying_obj->ptr));
                                delete underlying_obj;
                                break;
                            }
                            case Type_tag_for_input::type_in_forward_list: {
                                using underlying_container_specialization_and_thread_execution_policy = No_tag_template_type_info<std::forward_list<Polymoprhic_extensible_engine>>;
                                delete (static_cast<underlying_container_specialization_and_thread_execution_policy*>(underlying_obj->ptr));
                                delete underlying_obj;
                                break;
                            }
                            default:
                                break; 
                        }
                        break;
                    }

                    default:
                        throw std::string{"Invalid Type Tag during deletion"};
                        break;
                }
            }
            }

           
            };


                template<typename Op, bool op_action_type, absolute_base::Is_String_Or_Numeric Lhs_t>
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
                  template<typename Op, bool op_action_type, absolute_base::Is_String_Or_Numeric Rhs_t>
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
                template<typename Op, bool op_action_type>
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
            //todo :provide pump(functions that pump to string)
                                enum class actions: uint8_t{
                                    change_collection_of_types_tag=0,
                                    change_many_collections_of_types_tag=1,
                                    change_single_element_at_index_in_collection_of_types_tag=2,
                                    push_to_collection_of_types_tag,
                                    push_same_many_to_collection_of_types_tag,
                                    push_many_newly_read_to_collection_of_types_tag,
                                    pop_from_collection_of_types_tag,
                                    pop_many_from_collection_of_types_tag,
                                    insert_into_collection_of_types_tag,
                                    insert_same_many_into_collection_of_types_tag,
                                    insert_many_newly_read_into_collection_of_types_tag,
                                    change_part_of_lists_of_collection_of_types_tag,
                                    push_to_list_of_collection_of_types_tag,
                                    push_same_many_to_list_of_collection_of_types_tag,
                                    push_many_newly_read_to_list_of_collection_of_types_tag,
                                    pop_from_list_of_collection_of_types_tag,
                                    pop_many_from_list_of_collection_of_types_tag,
                                    insert_into_list_of_collection_of_types_tag,
                                    insert_same_many_into_list_of_collection_of_types_tag,
                                    insert_many_newly_read_into_list_of_collection_of_types_tag
                                };

                                inline void execute_action(const std::string& string_to_read_from, std::string::size_type* pos){
                                    actions what_to_do= static_cast<actions>(read_from_string<uint8_t>(string_to_read_from, pos));
                                    switch(what_to_do){
                                        case actions::change_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::change_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::change_many_collections_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::change_many_collections_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::change_single_element_at_index_in_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::change_single_element_at_index_in_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::push_to_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::push_to_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::push_same_many_to_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::push_same_many_to_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::push_many_newly_read_to_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::push_many_newly_read_to_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::pop_from_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::pop_from_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::pop_many_from_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::pop_many_from_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::insert_into_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::insert_into_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::insert_same_many_into_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::insert_same_many_into_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::insert_many_newly_read_into_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::insert_many_newly_read_into_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::change_part_of_lists_of_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::change_part_of_lists_of_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::push_to_list_of_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::push_to_list_of_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::push_same_many_to_list_of_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::push_same_many_to_list_of_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::push_many_newly_read_to_list_of_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::push_many_newly_read_to_list_of_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::pop_from_list_of_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::pop_from_list_of_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::pop_many_from_list_of_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::pop_many_from_list_of_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::insert_into_list_of_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::insert_into_list_of_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::insert_same_many_into_list_of_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::insert_same_many_into_list_of_collection_of_types(string_to_read_from, pos);
                                            break;
                                        case actions::insert_many_newly_read_into_list_of_collection_of_types_tag:
                                            type_information_storage_facilities_and_functions_to_access_them::main_interface_to_get_type_information::insert_many_newly_read_into_list_of_collection_of_types(string_to_read_from, pos);
                                            break;
                                        default:
                                            throw std::string{"invalid action!!!"};
                                    }
                                }
           
            


                
            //explicitly instantiating everything here because I just dont want this impossible to conquer file to stay in my head 
            //any longer:

            //arithemetic ops:
            
            template <typename T>
            struct exponentiation {
                T operator()(const T& base, const T& exp) const {
                    return std::pow(base, exp);
                }
            };
            
            // Arithmetic Ops
            template void op_generator<std::plus, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::minus, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::multiplies, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::divides, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::modulus, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            
            // Exponentiation (using the custom wrapper)
            template void op_generator<exponentiation, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            
            // Bitwise Ops
            template void op_generator<std::bit_and, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::bit_or, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::bit_xor, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::shift_left, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::shift_right, true, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            // comparision ops:
            template void op_generator<std::equal_to, false, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::not_equal_to, false, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::greater, false, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::less, false, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::greater_equal, false, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            template void op_generator<std::less_equal, false, Polymoprhic_extensible_engine, Polymoprhic_extensible_engine>();
            //didnt use weak ordering to avoid code bloat to get a more close to the metal behaviour for floating points
            Polymoprhic_extensible_engine read_polymorphically_from_string(const std::string& string_to_read_from, std::string:: std::size_type* pos) {
              Polymoprhic_extensible_engine(string_to_read_from, pos);
            }
            template <bool read_from_x_or_y>
            inline Polymoprhic_extensible_engine read_polymorphically_from_string(const std::string& x, const std::string& y, std::string:: std::size_type* x_pos, std::string:: std::size_type* y_pos) {
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








































































