# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "clang-format could not be found, please install it."
    exit 1
fi

# Get the clang-format version
CLANG_FORMAT_VERSION=$(clang-format --version)

# Run clang format for every .hpp .cpp and .inl files except gitignored ones
clang-format --verbose -i $(git ls-files --others --exclude-standard --cached | grep -E '\.hpp$|\.cpp$|\.inl$')
