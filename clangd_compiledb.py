Import("env")

# Include the board compiler headers in clangd's compilation database.
env.Replace(COMPILATIONDB_INCLUDE_TOOLCHAIN=True)
