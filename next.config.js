/**
 * @type {import('next').NextConfig}
 */
const nextConfig = {
    output: "export",
    // basePath: "/EpidemiologicLibraryWeb",
    // assetPrefix: '/EpidemiologicLibraryWeb/',
    images: {
        unoptimized: true,
    },
    trailingSlash: true,
}

module.exports = nextConfig