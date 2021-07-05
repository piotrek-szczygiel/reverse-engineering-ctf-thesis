# Setting up the website

Start CTFd:

```bash
sudo docker run -p 8000:8000 -it ctfd/ctfd
```

Start secret shell:

```bash
cd 500-secret-shell
sudo ./docker.sh
```

Main page:

```html
<div class="row">
    <div class="col-md-6 offset-md-3">
        <img class="w-100 mx-auto d-block" style="max-width: 350px;padding: 50px;padding-top: 14vh;" src="https://www.agh.edu.pl/fileadmin/default/templates/images/uczelnia/siw/znak/znak_wielobarwny/agh_znk_wbr_rgb_150ppi.jpg" />
        <h3 class="text-center">
            <p>AGH Reverse Engineering</p>
        </h3>
      <p class="text-center">Welcome! You have six reverse engineering challenges to solve.</p>
      <p class="text-center">Flag format: <i>AGH{example}</i></p>
    </div>
</div>
```

Secret shell description:

````
```text
$ ssh ctf@szczygiel.dev -p 2222
ctf@szczygiel.dev's password: agh-reverse-engineering
```
````
