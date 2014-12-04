int main()
{
    // write to a portion of memory that has marked as read-only
    char *str = "Foo";// compiler marks the constant string as read-only
    *str = 'b';//which means this is illegal and results in a segfault
    return 0;
}
