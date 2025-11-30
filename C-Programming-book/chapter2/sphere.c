#include <stdio.h>

#define PI 3.14159f // directives
#define SPHERE_VOLUME_FACTOR (4.0f / 3.0f)

int main (void)
{
    printf("Calculating volume of a predifened sphere...\n");
    float radius, volume;
    radius = 10.0f;

    volume = SPHERE_VOLUME_FACTOR * PI * radius * radius * radius;
    printf("Volume of sphere with radius %.2f is %.2f\n", radius, volume);

    float userRadius;
    float userVolume;

    printf("Calculating volume of a user-defined sphere...\n");
    printf("Enter radius: ");
    scanf("%f", &userRadius);

    userVolume = SPHERE_VOLUME_FACTOR * PI * userRadius * userRadius * userRadius;
    printf("Volume of sphere with radius %.2f is %.2f\n", userRadius, userVolume);

    return 0;

}
