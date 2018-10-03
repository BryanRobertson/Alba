#include "Graphics_Precompile.hpp"
#include "Graphics_Shader.hpp"
#include "Graphics_Module.hpp"
#include "Graphics_Service.hpp"
#include "Graphics_RenderBackEnd.hpp"
#include "Graphics_Debug.hpp"

#include "Core_Assert.hpp"
#include "Core_File.hpp"

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

				auto shader = handle.LockMutable(); 
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

			auto shader = handle.LockMutable();
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

			auto shader = handle.LockMutable();
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
		Shader::~Shader()
		{
			if (IsLoaded())
			{
				Unload();
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Shader::SetType(ShaderType aShaderType)
		{
			myShaderType = aShaderType;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Shader::LoadFromString(Core::StringView aShaderSourceCode)
		{
			ALBA_ASSERT(GraphicsModule::IsLoaded(), "Trying to load shader, but shader module is not loaded!");
	
			GraphicsModule& graphicsModule = GraphicsModule::Get();
			GraphicsService& graphicsService = graphicsModule.GetGraphicsServiceMutable();

			return graphicsService.CreateShaderFromString(GetId(), myShaderType, aShaderSourceCode) == 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Shader::LoadFromFile(Core::StringView aFileName)
		{
			ALBA_ASSERT(GraphicsModule::IsLoaded(), "Attempting to load shader, but graphics module is not loaded!");

			using Core::File;
			using Core::FileMode;
			
			File file = File::OpenFile(aFileName, { FileMode::Read, FileMode::Text });
			if (!file.IsOpen())
			{
				ALBA_LOG_ERROR(Graphics, "Failed to open shader file \"%s\"", aFileName.data());
				return false;
			}

			const auto buffer = file.ReadToEnd<char, 1024>();
			if (buffer.size() == 0)
			{
				ALBA_LOG_ERROR(Graphics, "Shader file \"%s\" was empty!", aFileName.data());
				return false;
			}

			GraphicsModule& graphicsModule = GraphicsModule::Get();
			GraphicsService& graphicsService = graphicsModule.GetGraphicsServiceMutable();

			const Core::StringView bufferView(buffer.data(), buffer.size());
			const ShaderId shaderId = GetId();

			const uint32 result = graphicsService.CreateShaderFromString(shaderId, myShaderType, bufferView);
			return result == 0;
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
			else if (IsLoaded() && GraphicsModule::IsLoaded())
			{
				GraphicsModule& graphicsModule = GraphicsModule::Get();
				GraphicsService& graphicsService = graphicsModule.GetGraphicsServiceMutable();

				graphicsService.UnloadShader(GetId());
			}
		}
	}
}
