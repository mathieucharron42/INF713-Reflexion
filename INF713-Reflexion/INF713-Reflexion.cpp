#include "Potato.h"

#include "ReflectionRepl.h"

#include "Type/TypeDescriptor.h"
#include "Type/TypeDescriptorFactory.h"
#include "Type/TypeLibrary.h"
#include "Type/TypeLibraryFactory.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdint.h>
#include <iosfwd>

using namespace Reflecto;

int main()
{
	const Reflection::TypeLibrary typeLibrary = Reflection::TypeLibraryFactory()
		.Add<std::string>("string")
		.Add<float>("float")
		.Add<int32_t>("int32")
		.Add<bool>("bool")
		.Add<void>("void")
		.BeginType<Potato>("Potato")
			.RegisterMember(&Potato::Type, "Type")
			.RegisterMember(&Potato::Weight, "Weight")
			.RegisterMember(&Potato::Calories, "Calories")
			.RegisterMember(&Potato::Sodium, "Sodium")
			.RegisterMember(&Potato::IsBaked, "IsBaked")
			.RegisterMethod(&Potato::Bake, "Bake")
			.RegisterMethod(&Potato::AddButter, "AddButter")
			.RegisterMethod(&Potato::AddSalt, "AddSalt")
		.EndType<Potato>()
	.Build();

	Serialization::Serializer serializer = Serialization::SerializerFactory(typeLibrary)
		.LearnType<int32_t, Serialization::Int32SerializationStrategy>()
		.LearnType<std::string, Serialization::StringSerializationStrategy>()
		.LearnType<float, Serialization::FloatSerializationStrategy>()
		.LearnType<bool, Serialization::BooleanSerializationStrategy>()
	.Build();

	Potato instance = Potato::BuildRusset();

	auto& input = std::cin;
	auto& ouput = std::cout;

	Reflection::Repl<Potato> repl;
	repl.Run(instance, typeLibrary, serializer, input, ouput);
}