function output = fourtwentycalc(readValue, lsv, hsv)
    output = ((readValue - lsv) / (hsv - lsv)) * 16e-3 + 4e-3;
end
