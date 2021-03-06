#pragma once

#include "Headers/ImageExportDirectory.h"
#include "Headers/ImageImportDirectory.h"
#include "Headers/ImageSectionHeader.h"
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

