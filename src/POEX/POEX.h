#pragma once

#include "Headers/ImageDelayImportDescriptor.h"
#include "Headers/ImageLoadConfigDirectory.h"
#include "Headers/ImageExceptionDirectory.h"
#include "Headers/ImageResourceDirectory.h"
#include "Headers/ImageExportDirectory.h"
#include "Headers/ImageImportDirectory.h"
#include "Headers/ImageDebugDirectory.h"
#include "Headers/ImageBaseRelocation.h"
#include "Headers/ImageSectionHeader.h"
#include "Headers/ImageTlsDirectory.h"
#include "Headers/ImageDosHeader.h"
#include "Headers/ImageNtHeader.h"
#include "Headers/IRaw.h"

namespace POEX
{
	class PE
	{
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="raw">PE raw data</param>
		PE(const std::vector<byte>& raw);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="filepath">PE file path</param>
		PE(CString filepath);

		/// Destructor
		~PE() = default;

		/// <summary>
		/// Get Image DOS Header structure
		/// </summary>
		/// <returns>Image DOS Header structure</returns>
		auto GetImageDosHeader()->ImageDosHeader;

		/// <summary>
		/// Get Image NT Header structure
		/// </summary>
		/// <returns>Image NT Header structure</returns>
		auto GetImageNtHeader()->ImageNtHeader;

		/// <summary>
		/// Get Image Section Header structures
		/// </summary>
		/// <returns>List of all Image Section Header</returns>
		auto GetImageSectionHeader()->std::vector<ImageSectionHeader>;

		/// <summary>
		/// Access to Image Export Directory and Export Functions
		/// </summary>
		/// <returns>Object of ImageExportDirector</returns>
		auto GetImageExportDirectory()->std::unique_ptr<ImageExportDirectory>;

		/// <summary>
		/// Access to Import Directory Table
		/// </summary>
		/// <returns>List of all Image Directory Table exist in PE.</returns>
		auto GetImageImportDirectory()->std::vector<std::unique_ptr<ImageImportDirectory>>;

		/// <summary>
		/// The resource directory contains icons, mouse pointer, string language files etc. 
		/// which are used by the application.
		/// </summary>
		/// <returns></returns>
		auto GetImageResourceDirectory() -> std::unique_ptr<ImageResourceDirectory>;

		/// <summary>
		/// Access to Image Exception Directory Table
		/// </summary>
		/// <returns></returns>
		auto GetImageExceptionDirectory() -> std::unique_ptr<ImageExceptionDirectory>;

		/// <summary>
		/// Access to Image TLS Directory
		/// </summary>
		/// <returns>Pointer of ImageTlsDirectory class</returns>
		auto GetImageTlsDirectory() -> std::unique_ptr<ImageTlsDirectory>;

		/// <summary>
		/// Access to Image Load Configuration Directory
		/// </summary>
		/// <returns></returns>
		auto GetImageLoadConfigDirectory() -> std::unique_ptr<ImageLoadConfigDirectory>;

		/// <summary>
		/// Access to Image Base Relocation
		/// </summary>
		/// <returns></returns>
		auto GetImageBaseRelocation() -> std::vector<std::unique_ptr<ImageBaseRelocation>>;

		/// <summary>
		/// Access to Delay Import Descriptor
		/// </summary>
		/// <returns>Pointer of ImageDelayImportDescriptor class</returns>
		auto GetImageDelayImportDescriptor() -> std::unique_ptr<ImageDelayImportDescriptor>;

		/// <summary>
		/// Access to Image Debug Directory
		/// </summary>
		/// <returns></returns>
		auto GetImageDebugDirectory() -> std::vector<std::unique_ptr<ImageDebugDirectory>>;

		/// <summary>
		/// Is the PE 64bit file?
		/// </summary>
		/// <returns>Return true if the PE is x64</returns>
		auto Is64Bit() const ->bool;

		/// <summary>
		/// Is the PE 32bit file?
		/// </summary>
		/// <returns>Return true if the PE is x32</returns>
		auto Is32Bit() const ->bool;

		/// <summary>
		/// is The PE executable file?
		/// </summary>
		/// <returns>Return true if the PE is executable file</returns>
		auto IsExe() ->bool;

		/// <summary>
		/// is the PE Dynamic Link Library(DLL) file?
		/// </summary>
		/// <returns>Return true if the PE is Dynamic Link Library(DLL) file</returns>
		auto IsDll() ->bool;

		/// <summary>
		/// Save the applied changes to the file
		/// </summary>
		/// <returns></returns>
		auto SaveFile() ->void;

		/// <summary>
		/// Save the applied changes to the file
		/// </summary>
		/// <param name="filepath">Save as another file(Keep original file)</param>
		/// <returns></returns>
		auto SaveFile(const CString& filepath)->void;

	private:
		PE() = default;

		CString filepath;
		std::shared_ptr<BufferFile> bFile;

		auto loadFile(const CString& filePath)->std::vector<byte>;
	};
}

