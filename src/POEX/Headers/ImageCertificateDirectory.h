#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include "BufferFile.h"

/// <summary>
/// WinCertificate wCertificateType constants.
/// </summary>
enum WinCertificateType : unsigned short
{
    /// <summary>
    ///     Certificate is X509 standard.
    /// </summary>
    X509 = 0x0001,

    /// <summary>
    ///     Certificate is PKCS signed data.
    /// </summary>
    PkcsSignedData = 0x0002,

    /// <summary>
    ///     Reserved
    /// </summary>
    Reserved1 = 0x0003,

    /// <summary>
    ///     Certificate is PKCS1 signature.
    /// </summary>
    Pkcs1Sign = 0x0009
};

/// <summary>
/// The ImageCertificateDirectory the information in the security directory of the PE file.
/// It contains information about any certificates used to sign the binary.
/// </summary>
class ImageCertificateDirectory
{
public:
	/// <summary>
	/// Create a new ImageCertificateDirectory object.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Offset of the structure in the buffer.</param>
	ImageCertificateDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset);
	~ImageCertificateDirectory() = default;

	/// <summary>
	/// Length of the certificate.
	/// </summary>
	/// <returns>Length of the certificate.</returns>
	auto DwLength() const -> unsigned int;

	/// <summary>
	/// Length of the certificate.
	/// </summary>
	/// <param name="length">Length of the certificate.</param>
	/// <returns></returns>
	auto DwLength(const unsigned int& length) -> void;

	/// <summary>
	/// Revision.
	/// </summary>
	/// <returns>Revision.</returns>
	auto WRevision() const -> unsigned short;

	/// <summary>
	/// Revision.
	/// </summary>
	/// <param name="revision">Revision.</param>
	/// <returns></returns>
	auto WRevision(const unsigned short& revision) -> void;

	/// <summary>
	/// The certificate type.
	/// </summary>
	/// <returns>The certificate type.</returns>
	auto WCertificateType() const -> WinCertificateType;

	/// <summary>
	/// The certificate type.
	/// </summary>
	/// <param name="type">The certificate type.</param>
	/// <returns></returns>
	auto WCertificateType(const WinCertificateType& type) -> void;

	/// <summary>
	/// The certificate.
	/// </summary>
	/// <returns>The certificate.</returns>
	auto BCertificate() const -> std::vector<byte>;

private:
	ImageCertificateDirectory() = default;
	ImageCertificateDirectory(const ImageCertificateDirectory&) = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;
};