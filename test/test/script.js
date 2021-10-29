let a = 12, b = 20;

(function somme(a, b) {
    if (b == 0) {
        return a;
    }

    else {
        return 1 + somme(a, b - 1);
    }

    console.log(somme());
})();

