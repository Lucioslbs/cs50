<! DOCTYPE html>

<html lang="en">
    <head>
        <script>

            function greet(){
                let name = document.querySelector('#name').value;
                alert('hello, ' + name);
            }

        </script>
        <title>hello</title>
    </head>
    <body>
        <form onsubmit="greet(); return false;">
            <input id="name" type="text">
                <input type="submit">
                </input>
            </input>
        </form>
    </body>
</html>
