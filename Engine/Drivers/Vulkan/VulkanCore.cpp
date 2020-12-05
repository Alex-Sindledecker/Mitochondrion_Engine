#include "mepch.h"
#include "VulkanCore.h"

#include "Core/Debug/EngineDebugger.h"

namespace vk
{

#ifdef _DEBUG
	const bool enableValidationLayers = true;
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
#else
	const bool enableValidationLayers = false;
	const std::vector<const char*> validationLayers;
#endif

	GLFWwindow* window;
	VkInstance instance;
	VkSurfaceKHR surface;

	bool init(GLFWwindow* windowPtr)
	{
		window = windowPtr;

		try
		{
			_createInstance();
			_createSurface();
		}
		catch (std::runtime_error e)
		{
			EngineDebugger::log(e.what(), EngineDebugger::LogType::ERR);
			return false;
		}
	}

	void terminate()
	{
	}

	void _createInstance()
	{
		//Check if using validation layers and that the required ones are supported
		if (enableValidationLayers && !_checkValidationLayerSupport())
			throw std::runtime_error("Validation layers requested, but not availible!");

		//Create the application info struct
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;					//struct type
		appInfo.pEngineName = "No Engine";									//Engine name
		appInfo.pApplicationName = "Vulkan App";							//Application name
		appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);				//Application version
		appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);					//Engine version
		appInfo.apiVersion = VK_VERSION_1_2;								//Vulkan API version

		//Get instance extensions and make sure they are supported
		uint32_t extensionCount = 0;
		const char** enabledExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);
		if (!_checkInstanceExtensionSupport(enabledExtensions, extensionCount))
			throw std::runtime_error("VK Instance does not support required extensions!");

		//Create the instance creation info struct
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;			//Struct type
		createInfo.pApplicationInfo = &appInfo;								//Reference to the app info created previously
		createInfo.enabledExtensionCount = extensionCount;					//How many extensions are enabled for the instance
		createInfo.ppEnabledExtensionNames = enabledExtensions;				//List of enabled extension names
		//Extra create info setttings if using validation layers
		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = validationLayers.size();			//How many validation layers are enabled
			createInfo.ppEnabledLayerNames = validationLayers.data();		//List of enabled validation layers
		}
		else
			createInfo.enabledLayerCount = 0;

		//Create the vulkan instance and assign it to instance
		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
			throw std::runtime_error("Failed to create vulkan instance!");
	}

	//Checks if the required validation layers are supported
	bool _checkValidationLayerSupport()
	{
		//Get the validation layer count
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		//Store the required validation layer properties in a list
		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		//Iterate through all of the validation layers that the application neeeds
		for (const char* validationLayer : validationLayers)
		{
			bool layerFound = false;
			//Iterate through the availible layers to ensure that validationLayer is in the availibleLayer names
			for (const VkLayerProperties& property : availableLayers)
			{
				if (strcmp(validationLayer, property.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}
			if (!layerFound)
				return false;
		}

		return true;
	}

	//Checks the instance to ensure all required extensions are supported
	bool _checkInstanceExtensionSupport(const char** extensions, int count)
	{
		//Get the number of available extensions
		uint32_t extensionCount;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		//Store all of the available extension properties in a list
		std::vector<VkExtensionProperties> properties(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, properties.data());

		//Iterate through all of the extensions that the device neeeds
		for (int i = 0; i < count; i++)
		{
			bool hasExtension = false;
			//Iterate through the availible extension properties to ensure that needed extension is in the extension names
			for (const VkExtensionProperties& prop : properties)
			{
				if (strcmp(extensions[i], prop.extensionName))
				{
					hasExtension = true;
					break;
				}
			}
			if (!hasExtension)
				return false;
		}

		return true;
	}

	//Create the surface for rendering to
	void _createSurface()
	{
		//Tell glfw to create a window surface
		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
			throw std::runtime_error("Failed to create surface!");
	}

}