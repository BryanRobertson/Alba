#pragma once

//-------------------------------------------------------------------------------------------------
// Name	:	Core_VariantMap.hpp
// Desc	:	Variant Map - Stores 
//-------------------------------------------------------------------------------------------------

#include "Core.hpp"
#include "Core_Variant.hpp"
#include "Core_AlignedStorage.hpp"
#include "Core_String.hpp"
#include "Core_StringHash.hpp"
#include "Core_Vector.hpp"
#include "Core_VectorMap.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_Pair.hpp"
#include "Core_HashMap.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	JSONObject
		// Desc	:	Store data in JSON format
		//-----------------------------------------------------------------------------------------
		class JSONObject final
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				struct NullType {};

				//=================================================================================
				// Public Constructors
				//=================================================================================
				JSONObject();
				~JSONObject();

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	Set(bool aValue);
				void	Set(float aValue);
				void	Set(double aValue);
				void	Set(int32 aValue);
				void	Set(int64 aValue);
				void	Set(const char* aValue);
				void	Set(const String& aValue);
				void	Set(const JSONObject& aValue);

				void	Set(const char* aKey, bool aValue);
				void	Set(const char* aKey, float aValue);
				void	Set(const char* aKey, double aValue);
				void	Set(const char* aKey, int32 aValue);
				void	Set(const char* aKey, int64 aValue);
				void	Set(const char* aKey, const char* aValue);
				void	Set(const char* aKey, const String& aValue);
				void	Set(const char* aKey, JSONObject&& aValue);
				void	Set(const char* aKey, const JSONObject& aValue);
				void	Set(const char* aKey, const Vector<JSONObject>& aValue);
				void	Set(const char* aKey, Vector<JSONObject>&& aValue);

				bool	IsBool() const;
				bool	IsFloat() const;
				bool	IsInteger() const;
				bool	IsString() const;
				bool	IsObject() const;
				bool	IsArray() const;

				bool	Get(bool& anOutValue);
				bool	Get(float& anOutValue);
				bool	Get(double& anOutValue);
				bool	Get(int32& anOutValue);
				bool	Get(int64& anOutValue);
				bool	Get(const char* anOutValue);
				bool	Get(String& anOutValue);
				bool	Get(JSONObject& anOutValue);

			private:

				//=================================================================================
				// Private Types
				//=================================================================================
				typedef Vector<Pair<String, JSONObject> >	DictionaryType;
				typedef Vector<JSONObject>					ArrayType;

				struct VTableBase
				{

				};

				template <typename TDataType>
				struct VTable : public VTableBase
				{
					const VTable<TDataType>* ourVTable = nullptr;
					const VTable<TDataType>* Get()
					{
						static VTable<TDataType> ourInstance;
						return &ourInstance;
					}
				};

				//=================================================================================
				// Private Data
				//=================================================================================
				const VTableBase*  myStorageVTable;
				AlignedStorage<40> myStorage;
		};
	}
}