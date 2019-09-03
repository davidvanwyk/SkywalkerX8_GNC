function isElement = halfPlaneCheck(p, r, n)

% Checks if p is an element of the half plane defined by r and n

if (p - r)'*n >= 0
   
    isElement = true;

else
   
    isElement = false;
    
end

end