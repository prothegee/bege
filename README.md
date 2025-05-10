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

this backend treatment is automatically using environment variables,

you need set your environment variables of or pass cmake config var:
1. `VCPKG_DIR` to your install vcpkg directory
2. `GODOT_CPP_DIR` to your godot-cpp directory, otherwise it error

### dependencies to install

- [openssl](https://github.com/openssl/openssl)

<br>

---

###### end of readme