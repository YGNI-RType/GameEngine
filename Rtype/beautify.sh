# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "clang-format could not be found, please install it."
    exit 1
fi

# Get the clang-format version
CLANG_FORMAT_VERSION=$(clang-format --version)

# Check if the version is 18.x.x
if [[ "$CLANG_FORMAT_VERSION" != *"18."* ]] && [[ "$CLANG_FORMAT_VERSION" != *"19."* ]]; then
    echo "Error: clang-format version 18.x.x or 19.x.x is required. Found: $CLANG_FORMAT_VERSION"
    exit 1
fi

make clean -C build || true
rm -r build/CMakeFiles || true
clang-format --verbose -i $(git ls-files --others --exclude-standard --cached | grep -E '\.hpp$|\.cpp$|\.inl$')
