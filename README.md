# bege

module library treatment for backend godot project

<br>

---

## platform and architect build, test, confirmed

| id | platform | x86_64 | arm64 | confirmed by |
| :- | :-       | :-     | :-    | :-           |
| 1  | linux    | ?      | ?     | n/a          |
| 2  | windows  | ?      | ?     | n/a          |
| 3  | osx      | ?      | ?     | n/a          |
| 4  | android  | ?      | ?     | n/a          |
| 5  | ios      | ?      | ?     | n/a          |

<br>

---

## important

this backend treatment is automatically using vcpkg,

you need set your environment variable of:
1. `VCPKG_DIR` to your install vcpkg directory, otherwise it error
2. `GODOT_CPP_DIR` to your godot-cpp directory, otherwise it error

### dependencies to install in vcpkg

- [openssl](https://github.com/openssl/openssl)

<br>

---

###### end of readme