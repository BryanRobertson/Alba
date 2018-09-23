#include "Graphics_Precompile.hpp"
#include "Graphics_Shader.hpp"
#include "Core_Assert.hpp"

namespace Alba
{
	namespace Graphics
	{
		static constexpr size_t ourMaxShaders = 2048;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API ShaderRepository final : public Core::ResourceRepository<Shader>
		{
			typedef Core::ResourceRepository<Shader> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				ShaderRepository();

				//=================================================================================
				// Public Methods
				//=================================================================================
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ShaderRepository::ShaderRepository()
			: Super(ourMaxShaders)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		namespace Detail
		{
			static ShaderRepository	ourShaderRepository;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ShaderHandle Shader::Get(ShaderType aShaderType, Core::StringView aFileName)
		{
			using namespace Detail;

			const Core::NoCaseStringHash32 resourceNameId(aFileName);

			ShaderHandle handle = Detail::ourShaderRepository.GetResource(resourceNameId);
			if (!handle.IsValid())
			{
				handle = ourShaderRepository.CreateResource(resourceNameId);
				ALBA_ASSERT(handle.IsValid(), "Failed to create resource \"%s\"", aFileName.data());

				Shader* shader = handle.LockMutable(); 
				shader->SetType(aShaderType);
				shader->SetFileName(aFileName);

				handle.Unlock();
			}

			return handle;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ ShaderHandle Shader::Get(Shader::NameId aResourceNameId)
		{
			using namespace Detail;
			return ourShaderRepository.GetResource(aResourceNameId);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ ShaderHandle Shader::CreateFromFile(ShaderType aShaderType, Core::StringView aFileName)
		{
			using namespace Detail;
			const Core::NoCaseStringHash32 resourceNameId(aFileName);

			ShaderHandle handle = ourShaderRepository.CreateResource(resourceNameId);
			ALBA_ASSERT(handle.IsValid(), "Failed to create resource \"%s\"", aFileName.data());

			Shader* shader = handle.LockMutable();
			shader->SetType(aShaderType);
			shader->SetFileName(aFileName);

			handle.Unlock();

			return handle;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ ShaderHandle Shader::CreateFromString(ShaderType aShaderType, NameId aNameId, Core::StringView /*aShaderSource*/)
		{
			using namespace Detail;
			ALBA_ASSERT(!ourShaderRepository.HasResource(aNameId), "Attempting to create duplicate shader \"%s\"", aNameId.LogString().c_str());

			ShaderHandle handle = ourShaderRepository.CreateResource(aNameId);
			ALBA_ASSERT(handle.IsValid(), "Failed to create resource \"%s\"", aNameId.LogString().c_str());

			Shader* shader = handle.LockMutable();
			shader->SetType(aShaderType);

			return handle;

		}
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Shader::Shader(Core::Resource<Shader>::NameIdType aResourceNameId, ShaderId aShaderId)
			: Super(aResourceNameId, aShaderId)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Shader::SetType(ShaderType aShaderType)
		{
			myShaderType = aShaderType;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Shader::LoadFromString(Core::StringView /*aShaderSourceCode*/)
		{
			return false;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Shader::CancelLoad()
		{
			if (IsLoading())
			{

			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Shader::Unload()
		{
			if (IsLoading())
			{
				CancelLoad();
			}
			else if (IsLoaded())
			{

			}
		}
	}
}
