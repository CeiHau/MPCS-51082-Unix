# HW6

## SAQ1
1. Yes, because the child process belongs to same user as parent, which is the file owner.

2. Yes, because the child can change the permission numerically to 0

3. No, because the child process belongs to the same user as parent.

4. No, child and parent have same permissions, the parent may only have access to opening that new file.

## SAQ2
1. It will show ```File name too long```

2. The terminal will not show anything


## SAQ3
we can use ```setpwent()``` function rewinds to the beginning of the password database and then use ```getpwent()``` repeatly to get each ```passwd``` structure that contains the record in password database. 

In ```passwd``` structure, we can use `passwd->pw_name` to check if it maches the argument `name` pass into `getpwnam()`.

Therefore, we can repeatly call ```getpwent()``` and get the return  `passwd` struct, then check the `passwd->pw_name`. If it matches, we can return the  `passwd` struct. Then use `endpwent()` to close the password database.



