# Programski jezik C: Savremeni pristup i praksa
<!-- 
## Struktura

`primeri/` - primeri sa predavanja, dorađeni da budu sami dovoljni i iskomentarisani.

`modern-c.pdf` - prezentacija sa predavanja -->

## Reference

- https://gustedt.wordpress.com/ -  novosti u C standardu, zanimljivi trikovi u jeziku C
- [Modern C, Jens Gustedt](http://icube-icps.unistra.fr/img_auth.php/d/db/ModernC.pdf) - knjiga koja pokriva C99 i C11 standarde
- [Secure Coding in C and C++, Robert C. Seacord](lepointdeau.fr/LIVRES/Pearson.Secure.2nd.Edition.Oct.2013.ISBN.0321822137.pdf) - česte ranjivosti C i C++ programa, načini na koje one budu iskorišćene, mehanizmi zaštite i njihova ograničenja.
- http://libcello.org/
- https://gcc.gnu.org/onlinedocs/gcc/C-Extensions.html
- https://gcc.gnu.org/onlinedocs/gcc/Attribute-Syntax.html
- https://github.com/Snaipe/libcsptr - PoC implementacija `unique_ptr` i `shared_ptr`-a u C-u
- https://www.youtube.com/user/Bisqwit - razni trikovi u C++-u (često primenljivi i u C-u). Realni primeri upotrebe X-makroa
- https://github.com/torvalds/linux
- https://github.com/cmus/cmus - strukture podataka iz primera, adaptirane iz linux-a za potrebe projekta
- [BalCCon 2k16 - Gannimo - Why we can't have nice things](https://www.youtube.com/watch?v=KgvocqMybZE) - Česte memorijske ranjivosti i ideje o njihovom rešavanju. Bezbednost printf funkcije. *printf-oriented programming*?

## Kontakt

Zaboravili ste da postavite pitanje? \
Nešto je ostalo nejasno?  \
Imate sugestije / kritike?

Pošaljite mi imejl na ` EMAIL(dusan.gvozdenovic.99)`, gde je:

```c
#define ID(X) X
#define STR(X) #X
#define $(X) STR(X)
#define DOMAIN gmail
#define TLD com
#define EMAIL(NAME) $(ID(NAME)ID(@)ID(DOMAIN)ID(.)ID(TLD))
```