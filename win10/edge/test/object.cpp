// Copyright 2015 Paul Vick
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "stdafx.h"
#include <vector>
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace jsrtwrapperstest
{
    TEST_CLASS(object)
    {
    public:
        MY_TEST_METHOD(empty_handle, "Test an empty object handle.")
        {
            jsrt::object handle;
            Assert::AreEqual(handle.handle(), JS_INVALID_REFERENCE);
            Assert::IsFalse(handle.is_valid());
        }

        MY_TEST_METHOD(no_context, "Test calls with no context.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            jsrt::object object;
            TEST_NO_CONTEXT_CALL(jsrt::object::create());
            TEST_NO_CONTEXT_CALL(jsrt::object::create(nullptr));
            {
				jsrt::context::scope scope(context);
				object = jsrt::object::create();
            }
            object.is_external();
            TEST_NO_CONTEXT_CALL(object.is_extension_allowed());
            TEST_NO_CONTEXT_CALL(object.prevent_extension());
            TEST_NO_CONTEXT_CALL(object.prototype());
            TEST_NO_CONTEXT_CALL(object.set_prototype(object));
            TEST_NO_CONTEXT_CALL(object.has_property(jsrt::property_id()));
            TEST_NO_CONTEXT_CALL(object.set_property(jsrt::property_id(), jsrt::value()));
            TEST_NO_CONTEXT_CALL(object.get_property(jsrt::property_id()));
            TEST_NO_CONTEXT_CALL(object.delete_property(jsrt::property_id()));
            TEST_NO_CONTEXT_CALL(object.get_own_property_descriptor(jsrt::property_id()));
            TEST_NO_CONTEXT_CALL(object.get_own_property_names());
            TEST_NO_CONTEXT_CALL(object.define_property(jsrt::property_id(), jsrt::property_descriptor<double>()));
            TEST_NO_CONTEXT_CALL(object.has_index(0));
            TEST_NO_CONTEXT_CALL(object.has_index(jsrt::string()));
            TEST_NO_CONTEXT_CALL(object.set_index(0, jsrt::value()));
            TEST_NO_CONTEXT_CALL(object.set_index(jsrt::string(), jsrt::value()));
            TEST_NO_CONTEXT_CALL(object.get_index(0));
            TEST_NO_CONTEXT_CALL(object.get_index(jsrt::string()));
            TEST_NO_CONTEXT_CALL(object.delete_index(0));
            TEST_NO_CONTEXT_CALL(object.delete_index(jsrt::string()));
            TEST_NO_CONTEXT_CALL(object.to_inspectable());

            jsrt::external_object external_object;
            TEST_NO_CONTEXT_CALL(jsrt::external_object::create());
			{
				jsrt::context::scope scope(context);
				external_object = jsrt::external_object::create();
			}
			external_object.data();
            external_object.set_data(nullptr);
            runtime.dispose();
        }

        MY_TEST_METHOD(invalid_handle, "Test calls with an invalid handle.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::object object;
                TEST_INVALID_ARG_CALL(object.is_external());
                TEST_INVALID_ARG_CALL(object.is_extension_allowed());
                TEST_INVALID_ARG_CALL(object.prevent_extension());
                TEST_INVALID_ARG_CALL(object.prototype());
                TEST_INVALID_ARG_CALL(object.set_prototype(object));
                TEST_INVALID_ARG_CALL(object.has_property(jsrt::property_id()));
                TEST_INVALID_ARG_CALL(object.set_property(jsrt::property_id(), jsrt::value()));
                TEST_INVALID_ARG_CALL(object.get_property(jsrt::property_id()));
                TEST_INVALID_ARG_CALL(object.delete_property(jsrt::property_id()));
                TEST_INVALID_ARG_CALL(object.get_own_property_descriptor(jsrt::property_id()));
                TEST_INVALID_ARG_CALL(object.get_own_property_names());
                TEST_INVALID_ARG_CALL(object.define_property(jsrt::property_id(), jsrt::property_descriptor<double>()));
                TEST_INVALID_ARG_CALL(object.has_index(0));
                TEST_INVALID_ARG_CALL(object.has_index(jsrt::string()));
                TEST_INVALID_ARG_CALL(object.set_index(0, jsrt::value()));
                TEST_INVALID_ARG_CALL(object.set_index(jsrt::string(), jsrt::value()));
                TEST_INVALID_ARG_CALL(object.get_index(0));
                TEST_INVALID_ARG_CALL(object.get_index(jsrt::string()));
                TEST_INVALID_ARG_CALL(object.delete_index(0));
                TEST_INVALID_ARG_CALL(object.delete_index(jsrt::string()));
                TEST_INVALID_ARG_CALL(object.to_inspectable());

                jsrt::external_object external_object;
                TEST_INVALID_ARG_CALL(external_object.data());
                TEST_INVALID_ARG_CALL(external_object.set_data(nullptr));

                jsrt::object valid_object = jsrt::object::create();
                TEST_INVALID_ARG_CALL(valid_object.set_prototype(jsrt::object()));
                TEST_INVALID_ARG_CALL(valid_object.has_property(jsrt::property_id()));
                TEST_INVALID_ARG_CALL(valid_object.set_property(jsrt::property_id(), jsrt::value()));
                TEST_INVALID_ARG_CALL(valid_object.set_property(jsrt::property_id::create(L"foo"), jsrt::value()));
                TEST_INVALID_ARG_CALL(valid_object.set_property(jsrt::property_id::create(jsrt::symbol::create(L"foo")), jsrt::value()));
                TEST_INVALID_ARG_CALL(valid_object.get_property(jsrt::property_id()));
                TEST_INVALID_ARG_CALL(valid_object.delete_property(jsrt::property_id()));
                TEST_INVALID_ARG_CALL(valid_object.get_own_property_descriptor(jsrt::property_id()));
                TEST_INVALID_ARG_CALL(valid_object.define_property(jsrt::property_id(), jsrt::property_descriptor<double>()));
                TEST_INVALID_ARG_CALL(valid_object.define_property(jsrt::property_id::create(L"foo"), jsrt::property_descriptor<double>()));
                TEST_INVALID_ARG_CALL(valid_object.define_property(jsrt::property_id::create(jsrt::symbol::create(L"foo")), jsrt::property_descriptor<double>()));
                TEST_INVALID_ARG_CALL(valid_object.has_index(jsrt::string()));
                TEST_INVALID_ARG_CALL(valid_object.set_index(0, jsrt::value()));
                TEST_INVALID_ARG_CALL(valid_object.set_index(jsrt::string(), jsrt::value()));
                TEST_INVALID_ARG_CALL(valid_object.set_index(jsrt::string::create(L"0"), jsrt::value()));
                TEST_INVALID_ARG_CALL(valid_object.get_index(jsrt::string()));
                TEST_INVALID_ARG_CALL(valid_object.delete_index(jsrt::string()));
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(create, "Test ::create method.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::value value = jsrt::object::create();
                jsrt::object object = static_cast<jsrt::object>(value);
                Assert::IsFalse(object.is_external());
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(extension, "Test ::is_extension_allowed and ::prevent_extension methods.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::object object = jsrt::object::create();
                Assert::IsTrue(object.is_extension_allowed());
                object.set_property(jsrt::property_id::create(L"foo"), 10);
                object.prevent_extension();
                Assert::IsFalse(object.is_extension_allowed());
                TEST_SCRIPT_EXCEPTION_CALL(object.set_property(jsrt::property_id::create(L"bar"), 20));
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(prototype, "Test ::prototype and ::set_prototype methods.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::object object = jsrt::object::create();
                object.prototype();
				jsrt::object prototype = jsrt::object::create();
                object.set_prototype(prototype);
                Assert::AreEqual(prototype.handle(), object.prototype().handle());
                object.prevent_extension();
                TEST_SCRIPT_EXCEPTION_CALL(object.set_prototype(jsrt::object::create()));
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(string_properties, "Test string property methods.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::object object = jsrt::object::create();

                object.set_property(jsrt::property_id::create(L"foo"), 10);
                object.set_property(jsrt::property_id::create(L"bar"), 20.0);
                object.set_property(jsrt::property_id::create(L"baz"), true);
                object.set_property(jsrt::property_id::create(L"x"), L"foo");
                object.set_property(jsrt::property_id::create(L"y"), object);

                Assert::AreEqual(object.get_property<int>(jsrt::property_id::create(L"foo")), 10);
                Assert::AreEqual(object.get_property<double>(jsrt::property_id::create(L"bar")), 20.0);
                Assert::AreEqual(object.get_property<bool>(jsrt::property_id::create(L"baz")), true);
                Assert::AreEqual(object.get_property<std::wstring>(jsrt::property_id::create(L"x")), static_cast<std::wstring>(L"foo"));
                Assert::AreEqual(object.get_property(jsrt::property_id::create(L"y")).handle(), object.handle());

                Assert::AreEqual(object.get_property(jsrt::property_id::create(L"z")).handle(), jsrt::context::undefined().handle());
                Assert::IsFalse(object.has_property(jsrt::property_id::create(L"z")));
                object.set_property(jsrt::property_id::create(L"z"), 10);
                Assert::IsTrue(object.has_property(jsrt::property_id::create(L"z")));
                Assert::AreEqual(object.get_property<double>(jsrt::property_id::create(L"z")), 10.0);
                object.delete_property(jsrt::property_id::create(L"z"));
                Assert::IsFalse(object.has_property(jsrt::property_id::create(L"z")));
                Assert::AreEqual(object.get_property(jsrt::property_id::create(L"z")).handle(), jsrt::context::undefined().handle());
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(symbol_properties, "Test symbol property methods.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);

                jsrt::symbol foo = jsrt::symbol::create(L"foo");
                jsrt::symbol bar = jsrt::symbol::create(L"bar");
                jsrt::symbol baz = jsrt::symbol::create(L"baz");
                jsrt::symbol x = jsrt::symbol::create(L"x");
                jsrt::symbol y = jsrt::symbol::create(L"y");
                jsrt::symbol z = jsrt::symbol::create(L"z");

                jsrt::object object = jsrt::object::create();

                object.set_property(jsrt::property_id::create(foo), 10);
                object.set_property(jsrt::property_id::create(bar), 20.0);
                object.set_property(jsrt::property_id::create(baz), true);
                object.set_property(jsrt::property_id::create(x), L"foo");
                object.set_property(jsrt::property_id::create(y), object);

                Assert::AreEqual(object.get_property<int>(jsrt::property_id::create(foo)), 10);
                Assert::AreEqual(object.get_property<double>(jsrt::property_id::create(bar)), 20.0);
                Assert::AreEqual(object.get_property<bool>(jsrt::property_id::create(baz)), true);
                Assert::AreEqual(object.get_property<std::wstring>(jsrt::property_id::create(x)), static_cast<std::wstring>(L"foo"));
                Assert::AreEqual(object.get_property(jsrt::property_id::create(y)).handle(), object.handle());

                Assert::AreEqual(object.get_property(jsrt::property_id::create(z)).handle(), jsrt::context::undefined().handle());
                Assert::IsFalse(object.has_property(jsrt::property_id::create(z)));
                object.set_property(jsrt::property_id::create(z), 10);
                Assert::IsTrue(object.has_property(jsrt::property_id::create(z)));
                Assert::AreEqual(object.get_property<double>(jsrt::property_id::create(z)), 10.0);
                object.delete_property(jsrt::property_id::create(z));
                Assert::IsFalse(object.has_property(jsrt::property_id::create(z)));
                Assert::AreEqual(object.get_property(jsrt::property_id::create(z)).handle(), jsrt::context::undefined().handle());
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(descriptors, "Test ::get_own_property_descriptor and ::define_property methods.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::object object = jsrt::object::create();

                jsrt::property_descriptor<double> desc = jsrt::property_descriptor<double>::create();
                desc.set_configurable(false);
                desc.set_writable(false);
                desc.set_value(10);

                object.define_property(jsrt::property_id::create(L"a"), desc);
                object.set_property(jsrt::property_id::create(L"a"), 20, false);
                Assert::AreEqual(object.get_property<double>(jsrt::property_id::create(L"a")), 10.0);
                TEST_SCRIPT_EXCEPTION_CALL(object.set_property(jsrt::property_id::create(L"a"), 20));
                TEST_SCRIPT_EXCEPTION_CALL(object.delete_property(jsrt::property_id::create(L"a")));

                jsrt::symbol a = jsrt::symbol::create(L"a");
                object.define_property(jsrt::property_id::create(a), desc);
                object.set_property(jsrt::property_id::create(a), 20, false);
                Assert::AreEqual(object.get_property<double>(jsrt::property_id::create(a)), 10.0);
                TEST_SCRIPT_EXCEPTION_CALL(object.set_property(jsrt::property_id::create(a), 20));
                TEST_SCRIPT_EXCEPTION_CALL(object.delete_property(jsrt::property_id::create(a)));
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(enumerable_string, "Test ::get_own_property_names.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::object object = jsrt::object::create();

                Assert::AreEqual(object.get_own_property_names().size(), static_cast<size_t>(0));
                object.set_property<double>(jsrt::property_id::create(L"a"), 10);
                jsrt::property_descriptor<double> desc = jsrt::property_descriptor<double>::create();
                desc.set_enumerable(false);
                desc.set_value(10);
                object.define_property(jsrt::property_id::create(L"b"), desc);
                object.set_property<double>(jsrt::property_id::create(jsrt::symbol::create(L"foo")), 10);

                std::vector<std::wstring> properties = object.get_own_property_names();
                Assert::AreEqual(properties.size(), static_cast<size_t>(2));
                Assert::AreEqual(properties[0], static_cast<std::wstring>(L"a"));
                Assert::AreEqual(properties[1], static_cast<std::wstring>(L"b"));
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(enumerable_symbol, "Test ::get_own_property_symbols.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::object object = jsrt::object::create();

                jsrt::symbol a = jsrt::symbol::create(L"a");
                jsrt::symbol b = jsrt::symbol::create(L"b");

                Assert::AreEqual(object.get_own_property_symbols().size(), static_cast<size_t>(0));
                object.set_property<double>(jsrt::property_id::create(a), 10);
                jsrt::property_descriptor<double> desc = jsrt::property_descriptor<double>::create();
                desc.set_enumerable(false);
                desc.set_value(10);
                object.define_property(jsrt::property_id::create(b), desc);
                object.set_property<double>(jsrt::property_id::create(L"foo"), 10);

                std::vector<jsrt::symbol> properties = object.get_own_property_symbols();
                Assert::AreEqual(properties.size(), static_cast<size_t>(2));
                Assert::IsTrue(properties[0].strict_equals(a));
                Assert::IsTrue(properties[1].strict_equals(b));
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(indexes, "Test indexed properties.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::object object = jsrt::object::create();

                object.set_index(0, 10);
                object.set_index(jsrt::string::create(L"1"), 20.0);
                object.set_index(3, true);
                object.set_index(jsrt::string::create(L"4"), L"foo");
                object.set_index(5, object);
                object.set_index(jsrt::string::create(L"x"), 30);

                TEST_INVALID_ARG_CALL(object.get_index<int>(jsrt::string::create(L"foo")));
                Assert::AreEqual(object.get_index<double>(jsrt::string::create(L"0")), 10.0);
                Assert::AreEqual(object.get_index<double>(1), 20.0);
                Assert::AreEqual(object.get_index<bool>(jsrt::string::create(L"3")), true);
                Assert::AreEqual(object.get_index<std::wstring>(4), static_cast<std::wstring>(L"foo"));
                Assert::AreEqual(object.get_index(jsrt::string::create(L"5")).handle(), object.handle());

                Assert::AreEqual(object.get_index(6).handle(), jsrt::context::undefined().handle());
                Assert::IsFalse(object.has_index(jsrt::string::create(L"6")));
                object.set_index(6, 10);
                Assert::IsTrue(object.has_index(6));
                Assert::AreEqual(object.get_index<double>(6), 10.0);
                object.delete_index(jsrt::string::create(L"6"));
                Assert::IsFalse(object.has_index(6));
                Assert::AreEqual(object.get_index(6).handle(), jsrt::context::undefined().handle());
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(external_indexes, "Test external indexed properties.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::object object = jsrt::object::create();

                Assert::IsFalse(object.has_external_indexes());
                auto array = jsrt::typed_array<int>::create({ 1, 2, 3, 4, 5 });
                Assert::AreEqual(array.get_index<int>(2), 3);
                object.set_external_indexes(array);
                Assert::IsTrue(object.has_external_indexes());
                Assert::AreEqual(object.external_indexes_type(), JsArrayTypeInt32);
                Assert::AreEqual(object.external_indexes_size(), 5u);
                Assert::IsNotNull(object.external_indexes_data());
                Assert::AreEqual(object.get_index<int>(2), 3);
            }
            runtime.dispose();
        }

        static void CALLBACK finalize(void *data)
        {
            Assert::AreEqual(data, reinterpret_cast<void *>(0xdeadbeef));
        }

        MY_TEST_METHOD(external, "Test external objects.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::value value = jsrt::external_object::create();
                jsrt::external_object object = static_cast<jsrt::external_object>(value);
                Assert::IsTrue(object.is_external());
                Assert::AreEqual(object.data(), static_cast<void *>(nullptr));
                object = jsrt::external_object::create(reinterpret_cast<void *>(0xdeadc0de), finalize);
                Assert::AreEqual(object.data(), reinterpret_cast<void *>(0xdeadc0de));
                object.set_data(reinterpret_cast<void *>(0xdeadbeef));
                Assert::AreEqual(object.data(), reinterpret_cast<void *>(0xdeadbeef));
                object = jsrt::external_object();
                runtime.collect_garbage();
            }
            runtime.dispose();
        }

        MY_TEST_METHOD(inspectable, "Test inspectable conversions.")
        {
            jsrt::runtime runtime = jsrt::runtime::create();
            jsrt::context context = runtime.create_context();
            {
                jsrt::context::scope scope(context);
                jsrt::context::project_uwp_namespace(L"Windows");
                auto uri = jsrt::context::evaluate(L"new Windows.Foundation.Uri('http://microsoft.com');");
                IInspectable *uri_ptr = static_cast<jsrt::object>(uri).to_inspectable();
                Assert::IsNotNull(uri_ptr);
                jsrt::object::create(uri_ptr);
            }
            runtime.dispose();
        }

    };
}